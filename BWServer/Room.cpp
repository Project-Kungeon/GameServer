#include "pch.h"
#include "Room.h"
#include "ObjectUtils.h"

RoomPtr GRoom[UINT16_MAX];

// 전역변수 GRoom 초기화
void Room::init()
{
	for (int i = 0; i < 3; i++)
	{
		GRoom[i] = std::make_shared<Room>();
	}

}

// 오브젝트의 Room 참가
bool Room::Join(ObjectPtr object)
{
	//_members.insert(member);
	bool success = AddObject(object);

	object->posInfo->set_x(RandomUtil::GetRandom(0.f, 500.f));
	object->posInfo->set_y(RandomUtil::GetRandom(0.f, 500.f));
	object->posInfo->set_z(100.f);
	object->posInfo->set_yaw(RandomUtil::GetRandom(0.f, 100.f));

	// 접속한 오브젝트가 플레이어라면..
	if (auto player = dynamic_pointer_cast<Player>(object))
	{
		message::S_EnterRoom enterRoomPkt;
		enterRoomPkt.set_success(true);
		enterRoomPkt.mutable_player_info()->CopyFrom(ObjectUtils::toPlayerInfo(player));
		if (auto session = player->session.lock())
		{
			const size_t requiredSize = PacketUtil::RequiredSize(enterRoomPkt);

			char* rawBuffer = new char[requiredSize];
			auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
			PacketUtil::Serialize(sendBuffer, message::HEADER::ENTER_ROOM_RES, enterRoomPkt);

			session->Send(sendBuffer);
		}
	}

	// 모든 클라이언트에게 New 오브젝트 스폰 명령
	{
		message::S_Spawn spawnPkt;
		if (auto player = dynamic_pointer_cast<Player>(object))
		{
			message::PlayerInfo* playerInfo = spawnPkt.add_players();
			playerInfo->CopyFrom(ObjectUtils::toPlayerInfo(player));
		}

		const size_t requiredSize = PacketUtil::RequiredSize(spawnPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_SPAWN_RES, spawnPkt);
		
		Broadcast(sendBuffer, object->objectInfo->object_id());
	}

	// 접속한 플레이어에게 전체 오브젝트 정보를 전달
	// TODO : 자기 자신 오브젝트는 보내면 안된다. 수정해야할 것.
	if (auto player = dynamic_pointer_cast<Player>(object))
	{
		message::S_Spawn spawnPkt;
		spdlog::info("{} Player에게 전달할 info 개수 : {}", object->objectInfo->object_id(), _objects.size());

		for (auto& item : _objects)
		{
			if (dynamic_pointer_cast<Player>(item.second) == nullptr) continue;
			if (item.first == player->objectInfo->object_id()) continue;
			if (auto otherPlayer = static_pointer_cast<Player>(item.second))
			{
				message::PlayerInfo* playerInfo = spawnPkt.add_players();
				playerInfo->CopyFrom(ObjectUtils::toPlayerInfo(otherPlayer));
			}
		}

		if (auto session = player->session.lock())
		{
			const size_t requiredSize = PacketUtil::RequiredSize(spawnPkt);

			char* rawBuffer = new char[requiredSize];
			auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
			PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_SPAWN_RES, spawnPkt);

			session->Send(sendBuffer);
		}
	}

	return success;
}

// 오브젝트가 방에서 나감
bool Room::Leave(ObjectPtr object)
{
	if (object == nullptr)
		return false;

	const uint64 object_id = object->objectInfo->object_id();
	bool success = RemoveObject(object_id);

	// 플레이어라면
	if (auto player = dynamic_pointer_cast<Player>(object))
	{
		message::S_LeaveRoom leaveRoomPkt;

		const size_t requiredSize = PacketUtil::RequiredSize(leaveRoomPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::LEAVE_ROOM_RES, leaveRoomPkt);

		if (auto session = player->session.lock())
		{
			session->Send(sendBuffer);
		}
	}

	// 다른 클라이언트에게 "Leave" 정보 브로드캐스트
	{
		message::S_Despawn despawnPkt;
		despawnPkt.add_object_ids(object_id);

		const size_t requiredSize = PacketUtil::RequiredSize(despawnPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_DESPAWN_RES, despawnPkt);

		Broadcast(sendBuffer, object_id);

		if (auto player = dynamic_pointer_cast<Player>(object))
			if (auto session = player->session.lock())
				session->Send(sendBuffer);
	}

	return success;
}

// 방에 접속한 모든 클라이언트에게 버퍼 전달
void Room::Broadcast(asio::mutable_buffer& buffer, uint64 exceptId)
{
	
	// 오브젝트 리스트 탐색
	for (auto& item : _objects)
	{
		// 플레이어 캐스팅
		PlayerPtr player = dynamic_pointer_cast<Player>(item.second);
		if (player == nullptr) continue;

		// 브로드캐스트 제외 대상은 보내지 않습니다.
		if (player->objectInfo->object_id() == exceptId) continue;

		if (GameSessionPtr session = player->session.lock())
		{
			spdlog::info("Broadcast to {} player", item.first);
			session->Send(buffer);
		}
	}

}

RoomPtr Room::GetRoomRef()
{
	return static_pointer_cast<Room>(shared_from_this());
}

bool Room::HandleEnterPlayer(PlayerPtr player)
{
	return Join(player);
}

bool Room::HandleLeavePlayer(PlayerPtr player)
{
	return Leave(player);
}

void Room::HandleMove(message::C_Move pkt)
{
	// is there object equals pkt's object id?
	const uint64 object_id = pkt.posinfo().object_id();

	// no object...
	if (_objects.find(object_id) == _objects.end())
		return;

	PlayerPtr player = dynamic_pointer_cast<Player>(_objects[object_id]);
	player->posInfo->CopyFrom(pkt.posinfo());

	// make buffer for notification that all client received.
	{
		message::S_Move movePkt;
		{
			message::PosInfo* posInfo = movePkt.mutable_posinfo();
			posInfo->CopyFrom(pkt.posinfo());
		}
		const size_t requiredSize = PacketUtil::RequiredSize(movePkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_MOVE_RES, movePkt);

		Broadcast(sendBuffer, object_id);
	}
}

void Room::HandleAttack(message::C_Attack pkt)
{
	uint64 attacker_id = pkt.object_id();
	uint32 damage = pkt.damage();

	
	if (_objects.find(attacker_id) != _objects.end())
	{
		message::S_Attack attackPkt;
		attackPkt.set_object_id(attacker_id);
		float damage = pkt.damage();
		auto attacker = static_pointer_cast<Creature>(_objects[attacker_id]);
		attackPkt.set_damage(pkt.damage());

		for (auto& victim_id : pkt.target_ids())
		{
			if (_objects.find(victim_id) != _objects.end())
			{
				auto victim = static_pointer_cast<Creature>(_objects[attacker_id]);
				victim->hp = victim->hp - damage;
				attackPkt.add_target_ids(victim_id);
			}
			
		}
		const size_t requiredSize = PacketUtil::RequiredSize(attackPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_ATTACK_RES, attackPkt);

		Broadcast(sendBuffer, 0);
		
	}

}

void Room::HandleWarriorAttack(skill::C_Warrior_Attack pkt)
{
	skill::S_Warrior_Attack attackPkt;
	attackPkt.set_object_id(pkt.object_id());

	const size_t requiredSize = PacketUtil::RequiredSize(attackPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::WARRIOR_ATTACK_RES, attackPkt);

	Broadcast(sendBuffer, pkt.object_id());
}

void Room::HandleWarriorR(skill::C_Warrior_R pkt)
{
	const uint64 object_id = pkt.object_id();
	if (_objects.find(object_id) != _objects.end())
	{
		PlayerPtr player = static_pointer_cast<Player>(_objects[object_id]);

		// 스킬 쿨타임 체크
		if (player->skillCoolTime->r_cooltime() > 0)
		{
			if (auto session = player->session.lock())
			{
				skill::S_CoolTime coolTimePkt;
				coolTimePkt.set_time(player->skillCoolTime->r_cooltime());
				coolTimePkt.set_skill_type(skill::SKILLTYPE::R);


				const size_t requiredSize = PacketUtil::RequiredSize(coolTimePkt);
				char* rawBuffer = new char[requiredSize];
				auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
				PacketUtil::Serialize(sendBuffer, message::HEADER::COOLTIME_RES, coolTimePkt);

				session->Send(sendBuffer);
				return;
			}
		}
		else
		{
			player->skillCoolTime->set_r_cooltime(20000);
		}
	}

	

	skill::S_Warrior_R skillPkt;
	skillPkt.set_object_id(pkt.object_id());

	const size_t requiredSize = PacketUtil::RequiredSize(skillPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::WARRIOR_R_RES, skillPkt);

	Broadcast(sendBuffer, 0);
}

void Room::HandleWarriorE(skill::C_Warrior_E pkt)
{
	const uint64 object_id = pkt.object_id();
	if (_objects.find(object_id) != _objects.end())
	{
		PlayerPtr player = static_pointer_cast<Player>(_objects[object_id]);

		// 스킬 쿨타임 체크
		if (player->skillCoolTime->e_cooltime() > 0)
		{
			if (auto session = player->session.lock())
			{
				skill::S_CoolTime coolTimePkt;
				coolTimePkt.set_time(player->skillCoolTime->e_cooltime());
				coolTimePkt.set_skill_type(skill::SKILLTYPE::E);

				const size_t requiredSize = PacketUtil::RequiredSize(coolTimePkt);
				char* rawBuffer = new char[requiredSize];
				auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
				PacketUtil::Serialize(sendBuffer, message::HEADER::COOLTIME_RES, coolTimePkt);

				session->Send(sendBuffer);
				return;
			}
		}
		else
		{
			player->skillCoolTime->set_e_cooltime(10000);
		}
	}

	skill::S_Warrior_E skillPkt;
	skillPkt.set_object_id(pkt.object_id());

	const size_t requiredSize = PacketUtil::RequiredSize(skillPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::WARRIOR_E_RES, skillPkt);

	Broadcast(sendBuffer, 0);
}

void Room::HandleAssassinAttack(skill::C_ASSASSIN_Attack pkt)
{
	skill::S_ASSASSIN_Attack attackPkt;
	attackPkt.set_object_id(pkt.object_id());

	const size_t requiredSize = PacketUtil::RequiredSize(attackPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::ASSASSIN_ATTACK_RES, attackPkt);

	Broadcast(sendBuffer, pkt.object_id());
}

void Room::HandleAssassinQ(skill::C_ASSASSIN_Q pkt)
{
	const uint64 object_id = pkt.object_id();
	if (_objects.find(object_id) != _objects.end())
	{
		PlayerPtr player = static_pointer_cast<Player>(_objects[object_id]);

		// 스킬 쿨타임 체크
		if (player->skillCoolTime->q_cooltime() > 0)
		{
			if (auto session = player->session.lock())
			{
				skill::S_CoolTime coolTimePkt;
				coolTimePkt.set_time(player->skillCoolTime->r_cooltime());
				coolTimePkt.set_skill_type(skill::SKILLTYPE::Q);

				const size_t requiredSize = PacketUtil::RequiredSize(coolTimePkt);
				char* rawBuffer = new char[requiredSize];
				auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
				PacketUtil::Serialize(sendBuffer, message::HEADER::COOLTIME_RES, coolTimePkt);

				session->Send(sendBuffer);
				return;
			}

		}
		else
		{
			player->skillCoolTime->set_q_cooltime(5000);
		}
		skill::S_ASSASSIN_Q skillPkt;
		skillPkt.set_object_id(pkt.object_id());
		skillPkt.set_x(pkt.x());
		skillPkt.set_y(pkt.y());
		skillPkt.set_z(pkt.z());
		skillPkt.set_yaw(pkt.yaw());

		const size_t requiredSize = PacketUtil::RequiredSize(skillPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::ASSASSIN_Q_RES, skillPkt);

		Broadcast(sendBuffer, 0);
	}
}

void Room::HandleAssassinR(skill::C_ASSASSIN_R pkt)
{
	const uint64 object_id = pkt.object_id();
	if (_objects.find(object_id) != _objects.end())
	{
		PlayerPtr player = static_pointer_cast<Player>(_objects[object_id]);

		// 스킬 쿨타임 체크
		if (player->skillCoolTime->r_cooltime() > 0)
		{
			if (auto session = player->session.lock())
			{
				skill::S_CoolTime coolTimePkt;
				coolTimePkt.set_time(player->skillCoolTime->r_cooltime());
				coolTimePkt.set_skill_type(skill::SKILLTYPE::R);

				const size_t requiredSize = PacketUtil::RequiredSize(coolTimePkt);
				char* rawBuffer = new char[requiredSize];
				auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
				PacketUtil::Serialize(sendBuffer, message::HEADER::COOLTIME_RES, coolTimePkt);

				session->Send(sendBuffer);
				return;
			}

		}
		else
		{
			player->skillCoolTime->set_r_cooltime(20000);
		}
		skill::S_ASSASSIN_R skillPkt;
		skillPkt.set_object_id(pkt.object_id());

		const size_t requiredSize = PacketUtil::RequiredSize(skillPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::ASSASSIN_R_RES, skillPkt);

		Broadcast(sendBuffer, 0);
	}
}

void Room::HandleAssassinLS(skill::C_ASSASSIN_LS pkt)
{
	const uint64 object_id = pkt.object_id();
	if (_objects.find(object_id) != _objects.end())
	{
		PlayerPtr player = static_pointer_cast<Player>(_objects[object_id]);

		// 스킬 쿨타임 체크
		if (player->skillCoolTime->ls_cooltime() > 0)
		{
			if (auto session = player->session.lock())
			{
				skill::S_CoolTime coolTimePkt;
				coolTimePkt.set_time(player->skillCoolTime->r_cooltime());
				coolTimePkt.set_skill_type(skill::SKILLTYPE::LS);

				const size_t requiredSize = PacketUtil::RequiredSize(coolTimePkt);
				char* rawBuffer = new char[requiredSize];
				auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
				PacketUtil::Serialize(sendBuffer, message::HEADER::COOLTIME_RES, coolTimePkt);

				session->Send(sendBuffer);
				return;
			}

		}
		else
		{
			player->skillCoolTime->set_ls_cooltime(5000);
		}
		skill::S_ASSASSIN_LS skillPkt;
		skillPkt.set_object_id(pkt.object_id());

		const size_t requiredSize = PacketUtil::RequiredSize(skillPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::ASSASSIN_LS_RES, skillPkt);

		Broadcast(sendBuffer, 0);
	}
}

void Room::HandleCoolTime(long long elapsed_millisecond)
{
	for (auto& item : _objects)
	{
		const uint64 object_id = item.first;
		if (auto player = dynamic_pointer_cast<Player>(item.second))
		{
			int decrement = elapsed_millisecond;
			int qCooltime = player->skillCoolTime->q_cooltime();
			int eCooltime = player->skillCoolTime->e_cooltime();
			int rCooltime = player->skillCoolTime->r_cooltime();
			int lsCooltime = player->skillCoolTime->ls_cooltime();
			if (qCooltime > 0)
			{
				player->skillCoolTime->set_q_cooltime(
					qCooltime - decrement > 0 ? 
					qCooltime - decrement : 0
				);
			}
			if (eCooltime > 0)
			{
				player->skillCoolTime->set_e_cooltime(
					eCooltime - decrement > 0 ?
					eCooltime - decrement : 0
				);
			}
			if (rCooltime > 0)
			{
				player->skillCoolTime->set_r_cooltime(
					rCooltime - decrement > 0 ?
					rCooltime - decrement : 0
				);
				spdlog::info("R cooltime : {}", ((float)rCooltime - decrement) / 1000);
			}
			if (lsCooltime > 0)
			{
				player->skillCoolTime->set_ls_cooltime(
					lsCooltime - decrement > 0 ?
					lsCooltime - decrement : 0
				);
			}
		}
	}
}

// Room의 STL에 오브젝트 추가
bool Room::AddObject(ObjectPtr object)
{
	// Is there already same object in room..
	if (_objects.find(object->objectInfo->object_id()) != _objects.end())
	{
		return false;
	}
	_objects.insert({ object->objectInfo->object_id(), object });
	object->room.store(GetRoomRef());

	return true;
}

// Room의 STL에 오브젝트 삭제
bool Room::RemoveObject(uint64 objectId)
{
	// 해당 아이디가 존재하지 않다면
	if (_objects.find(objectId) == _objects.end())
		return false;

	ObjectPtr object = _objects[objectId];
	object->room.store(std::weak_ptr<Room>());

	_objects.erase(objectId);

	return true;
}
