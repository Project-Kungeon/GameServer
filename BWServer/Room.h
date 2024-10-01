#pragma once
#include "Member.h"
#include "Message.pb.h"
#include "Skill.pb.h"
#include "MonsterPattern.pb.h"
#include "JobQueue.h"
using namespace std;

class Room : public JobQueue
{
public:
	Room(boost::asio::io_context& io_context)
		: JobQueue(io_context)
	{}

	static void init(boost::asio::io_context& io_context);
	bool Join(ObjectPtr object);
	bool Leave(ObjectPtr object);
	std::weak_ptr<Player> FindClosePlayerBySelf(CreaturePtr Self, const float Distance);
	void Broadcast(asio::mutable_buffer& buffer, uint64 exceptId);
	RoomPtr GetRoomRef();

	bool HandleEnterPlayer(PlayerPtr player);
	bool HandleLeavePlayer(PlayerPtr player);
	bool SpawnMonster(MonsterPtr monster);
	void HandleMove(message::C_Move pkt);
	void HandleAttack(message::C_Attack pkt);
	void HandleDeath(CreaturePtr creature);

	void HandleWarriorAttack(skill::C_Warrior_Attack pkt);
	void HandleWarriorR(skill::C_Warrior_R pkt);
	void HandleWarriorE(skill::C_Warrior_E pkt);
	void HandleWarriorLS(skill::C_Warrior_LS pkt);


	void HandleAssassinAttack(skill::C_ASSASSIN_Attack pkt);
	void HandleAssassinQ(skill::C_ASSASSIN_Q pkt);
	void HandleAssassinR(skill::C_ASSASSIN_R pkt);
	void HandleAssassinLS(skill::C_ASSASSIN_LS pkt);
	void HandleAssassinLSOff(AssassinPtr assassin, uint64 object_id);
	void HandleAssassinE(skill::C_Assassin_E pkt);

	void HandleArchorAttack(skill::C_Archor_Attack& pkt);
	void HandleArchorQ_Charging(skill::C_Archor_Q_Charging& pkt);
	void HandleArchorQ_Shot(skill::C_Archor_Q_Shot& pkt);
	void HandleArchorE(skill::C_Archor_E& pkt);
	void HandleArchorR(skill::C_Archor_R& pkt);
	void HandleArchorR_Off(ArchorPtr archor, uint64 object_id);
	void HandleArchorLS(skill::C_Archor_LS& pkt);
	void HandleArchorLS_Off(ArchorPtr archor, uint64 object_id);

	void SendRampageBasicAttack(RampagePtr rampage);
	void SendRampageMoveToTarget(RampagePtr rampage, CreaturePtr target);
	void SendRamapgeRoar(RampagePtr rampage);
	void SendRampageEarthQuake(RampagePtr rampage);
	void SendRamapgeTurnToTarget(RampagePtr rampage, CreaturePtr target);

	// Tick
public:
	void HandleTick(uint32 Deltatime);
	void HandleCoolTime(long long elapsed_millisecond);
	void HandleBuffTime(long long elapsed_millisecond);

private:
	bool AddObject(ObjectPtr object);
	bool RemoveObject(uint64 objectId);

private:
	USE_LOCK;
	unordered_map<uint64, ObjectPtr> _objects;
};

extern RoomPtr GRoom[UINT16_MAX];