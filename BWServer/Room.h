#pragma once
#include "Member.h"
#include "Message.pb.h"
#include "Skill.pb.h"
using namespace std;

class Room : public std::enable_shared_from_this<Room>
{
public:
	static void init();
	bool Join(ObjectPtr object);
	bool Leave(ObjectPtr object);
	void Broadcast(asio::mutable_buffer& buffer, uint64 exceptId);
	RoomPtr GetRoomRef();

	bool HandleEnterPlayer(PlayerPtr player);
	bool HandleLeavePlayer(PlayerPtr player);
	void HandleMove(message::C_Move pkt);
	void HandleAttack(message::C_Attack pkt);

	void HandleWarriorAttack(skill::C_Warrior_Attack pkt);
	void HandleWarriorR(skill::C_Warrior_R pkt);
	void HandleWarriorE(skill::C_Warrior_E pkt);

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
	void HandleArchorLS(skill::C_Archor_LS& pkt);

	// Tick
public:
	void HandleCoolTime(long long elapsed_millisecond);

private:
	bool AddObject(ObjectPtr object);
	bool RemoveObject(uint64 objectId);

private:
	set<MemberPtr> _members;
	unordered_map<uint64, ObjectPtr> _objects;
};

extern RoomPtr GRoom[UINT16_MAX];