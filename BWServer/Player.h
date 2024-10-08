#pragma once
#include "Creature.h"
class Player : public Creature
{
public:
	Player();
	Player(
		message::PlayerType playerType,
		float hp,
		float maxHp,
		float exp,
		const uint32 Q_COOLTIME,
		const uint32 E_COOLTIME,
		const uint32 R_COOLTIME,
		const uint32 LS_COOLTIME);
	virtual ~Player();

public:
	virtual void Tick(uint32 DeltaTime);
	virtual void UseSkillQ();
	virtual void UseSkillE();
	virtual void UseSkillR();
	virtual void UseSkillLS();

public:
	std::weak_ptr<GameSession> session;

	// Get&Set
public:
	const message::SkillCooltime* GetSkillCooltime() { GetReadLock();  return skillCoolTime; };
	void SetQ_Cooltime(uint32 cooltime);
	void SetE_Cooltime(uint32 cooltime);
	void SetR_Cooltime(uint32 cooltime);
	void SetLS_Cooltime(uint32 cooltime);
	const uint32 GetQ_Cooltime() { return GetSkillCooltime()->q_cooltime(); }
	const uint32 GetE_Cooltime() { return GetSkillCooltime()->e_cooltime(); }
	const uint32 GetR_Cooltime() { return GetSkillCooltime()->r_cooltime(); }
	const uint32 GetLS_Cooltime() { return  GetSkillCooltime()->ls_cooltime(); }
	vector<uint32> GetCooltimes() 
	{ GetReadLock(); vector<uint32> cooltimes; 
	cooltimes.push_back(skillCoolTime->q_cooltime()); cooltimes.push_back(skillCoolTime->e_cooltime());
	cooltimes.push_back(skillCoolTime->r_cooltime()); cooltimes.push_back(skillCoolTime->ls_cooltime());
	return cooltimes;
	}
	message::PlayerType GetPlayerType() { GetReadLock(); return playerType; }

	const uint32 GetMaxQ_Cooltime() { return Q_COOLTIME; }

private:
	message::PlayerType playerType;
	message::SkillCooltime* skillCoolTime;

public:
	const uint32 Q_COOLTIME;
	const uint32 E_COOLTIME;
	const uint32 R_COOLTIME;
	const uint32 LS_COOLTIME;
};

