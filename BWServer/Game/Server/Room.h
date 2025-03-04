#pragma once
#include "Member.h"
#include "Message.pb.h"
#include "Skill.pb.h"
#include "Item.pb.h"
#include "MonsterPattern.pb.h"
#include "JobQueue/JobQueue.h"

using namespace std;

class Room : public JobQueue
{
public:
	Room(boost::asio::io_context& io_context)
		: JobQueue(io_context)
	{}

	static void init(boost::asio::io_context& io_context);
	void RegisterGameServer(GameServerPtr game_server);
	bool Join(ObjectPtr object, bool pos_setted);
	bool Leave(ObjectPtr object);
	std::weak_ptr<Player> FindClosePlayerBySelf(CreaturePtr Self, const float Distance);
	void UdpBroadcast(asio::mutable_buffer& buffer, uint64 exceptId);
	void Broadcast(google::protobuf::Message& msg, const short packetCode, uint64 exceptId);
	void Broadcast(BufferPtr buffer, size_t requiredSize, uint64 exceptId);
	void DelayBroadcast(google::protobuf::Message& msg, const short packetCode, uint64 exceptId);
	RoomPtr GetRoomRef();

	virtual bool HandleEnterPlayer(PlayerPtr player);
	virtual bool HandleLeavePlayer(PlayerPtr player);
	virtual bool SpawnMonster(MonsterPtr monster);
	virtual bool SpawnObject(ObjectPtr monster);
	virtual void SendMove(message::S_Move pkt);
	virtual void HandleMove(message::C_Move pkt);
	virtual void HandleAttack(message::C_Attack pkt);
	virtual void HandleDeath(CreaturePtr creature);

	void HandleWarriorAttack(skill::C_Warrior_Attack pkt);
	void HandleWarriorQ(skill::C_Warrior_Q pkt);
	void HandleWarriorQ_Hit(skill::C_Warrior_Q_Hit pkt);

	void HandleWarriorR(skill::C_Warrior_R pkt);
	void HandleWarriorE(skill::C_Warrior_E pkt);
	void HandleWarriorE_Success(skill::C_Warrior_E_Success pkt);
	void HandleWarriorLS(skill::C_Warrior_LS pkt);


	void HandleAssassinAttack(skill::C_ASSASSIN_Attack pkt);
	void HandleAssassinQ(skill::C_ASSASSIN_Q pkt);
	void HandleAssassinR(skill::C_ASSASSIN_R pkt);
	void HandleAssassinLS(skill::C_ASSASSIN_LS pkt);
	void HandleAssassinLSOff(AssassinPtr assassin, uint64 object_id);
	void HandleAssassinE(skill::C_Assassin_E pkt);

	void HandleArchorAttack(skill::C_Archor_Attack pkt);
	void HandleArchorQ_Charging(skill::C_Archor_Q_Charging pkt);
	void HandleArchorQ_Shot(skill::C_Archor_Q_Shot pkt);
	void HandleArchorE(skill::C_Archor_E pkt);
	void HandleArchorR(skill::C_Archor_R pkt);
	void HandleArchorR_Off(ArchorPtr archor, uint64 object_id);
	void HandleArchorLS(skill::C_Archor_LS pkt);
	void HandleArchorLS_Off(ArchorPtr archor, uint64 object_id);

	void SendRampageBasicAttack(RampagePtr rampage);
	void SendRampageMoveToTarget(RampagePtr rampage, CreaturePtr target);
	void SendRampageMoveToPos(RampagePtr rampage, int rand_x, int rand_y, int rand_z);
	void SendRamapgeRoar(RampagePtr rampage);
	void SendRampageEarthQuake(RampagePtr rampage);
	void SendRamapgeTurnToTarget(RampagePtr rampage, CreaturePtr target);
	void SendRampageEnhancedAttack(RampagePtr rampage);

	void HandleItemPickedUp(PlayerPtr player, game::item::C_Item_PickedUp pkt);
	void HandleItemConsumeableUsed(PlayerPtr player, game::item::C_Item_ConsumeableUsed pkt);
	void HandleItemOpenOpenInventory(PlayerPtr player, game::item::C_Item_OpenInventory pkt);

	void BroadcastHealCreature(CreaturePtr creature, float health);

public:
	void BroadcastPingPacket();

	std::shared_ptr<boost::asio::steady_timer> _tickTimer;
	void StartTickTimer() {
		if (!_tickTimer) {
			_tickTimer = std::make_shared<boost::asio::steady_timer>(_strand);
		}

		_tickTimer->expires_after(std::chrono::milliseconds(_currentInterval.count()));

		std::weak_ptr<Room> weak_self = static_pointer_cast<Room>(shared_from_this());
		_tickTimer->async_wait(
			boost::asio::bind_executor(_strand,
				[weak_self](const boost::system::error_code& error) {
					if (auto self = weak_self.lock()) {
						if (!error) {
							self->HandleTick(1000);  // 틱 처리
							self->StartTickTimer(); // 다음 틱 예약
						}
					}
				}
			)
		);
	}
	// Tick
public:
	virtual void HandleTick(uint32 Deltatime);
	void HandleCoolTime(long long elapsed_millisecond);
	void HandleBuffTime(long long elapsed_millisecond);

private:
	bool AddObject(ObjectPtr object);
	bool RemoveObject(uint64 objectId);

private:
	USE_LOCK;
	unordered_map<uint64, ObjectPtr> _objects;

private:
	std::chrono::steady_clock::time_point _lastTickTime;
	std::chrono::steady_clock::time_point _startTime;
	int _tickCount = 0;
	int test_tick_cnt = 0;
	const int _targetTicksPerSecond = 45;
	const std::chrono::milliseconds _targetTickInterval{1000 / _targetTicksPerSecond};
	const std::chrono::seconds _measurementPeriod{10}; // 10초 동안 측정
	std::chrono::milliseconds _currentInterval{1000}; // 초기 간격

	GameServerPtr _GameServer;
};

extern RoomPtr GRoom[UINT16_MAX];