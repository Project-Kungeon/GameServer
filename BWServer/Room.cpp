#include "pch.h"
#include "Room.h"

extern RoomPtr GRoom[UINT16_MAX];

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

		message::ObjectInfo* objectInfo = new message::ObjectInfo();
		objectInfo->CopyFrom(*player->objectInfo);
		enterRoomPkt.set_allocated_player(objectInfo);
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
		message::ObjectInfo* objectInfo = spawnPkt.add_players();
		objectInfo->CopyFrom(*object->objectInfo);

		const size_t requiredSize = PacketUtil::RequiredSize(spawnPkt);
		char* rawBuffer = new char[requiredSize];
		auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
		PacketUtil::Serialize(sendBuffer, message::HEADER::PLAYER_SPAWN_RES, spawnPkt);
		
		Broadcast(sendBuffer, object->objectInfo->object_id());
	}

	return success;
}

// 오브젝트가 방에서 나감
bool Room::Leave(ObjectPtr object)
{
	if (object == nullptr)
		return false;

	const unsigned int object_id = object->objectInfo->object_id();
	RemoveObject(object_id);

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
}

// 방에 접속한 모든 클라이언트에게 버퍼 전달
void Room::Broadcast(asio::mutable_buffer& buffer, unsigned int exceptId)
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
			session->Send(buffer);
		}
	}

}

// TODO
bool Room::HandleEnterPlayer(PlayerPtr player)
{
	return Join(player);
}

bool Room::HandleLeavePlayer(PlayerPtr player)
{
}

void Room::HandleMovePlayer(PlayerPtr player)
{
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

	return true;
}

// Room의 STL에 오브젝트 삭제
bool Room::RemoveObject(unsigned int objectId)
{
	// 해당 아이디가 존재하지 않다면
	if (_objects.find(objectId) == _objects.end())
		return false;

	ObjectPtr object = _objects[objectId];
	object->room.store(std::weak_ptr<Room>());

	_objects.erase(objectId);

	return false;
}
