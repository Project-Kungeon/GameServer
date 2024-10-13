#include "pch.h"
#include "Player.h"

Player::Player()
	: Creature(),
	playerType(message::PLAYER_TYPE_NONE),
	Q_COOLTIME(1000),
	E_COOLTIME(1000),
	R_COOLTIME(1000),
	LS_COOLTIME(1000),
	skillCoolTime(new message::SkillCooltime())
{	
}

Player::Player(
	message::PlayerType playerType,
	float hp,
	float maxHp,
	float exp,
	const uint32 Q_COOLTIME,
	const uint32 E_COOLTIME,
	const uint32 R_COOLTIME,
	const uint32 LS_COOLTIME)
	: Creature(message::CREATURE_TYPE_PLAYER, hp, maxHp, exp),
	playerType(playerType),
	Q_COOLTIME(Q_COOLTIME),
	E_COOLTIME(E_COOLTIME),
	R_COOLTIME(R_COOLTIME),
	LS_COOLTIME(LS_COOLTIME),
	skillCoolTime(new message::SkillCooltime())
{
}

void Player::InitInventory()
{
	_inventory.store(std::make_shared<Inventory>(static_pointer_cast<Player>(shared_from_this())));
}

Player::~Player()
{
	delete skillCoolTime;
	skillCoolTime = nullptr;
}

void Player::Tick(uint32 DeltaTime)
{
	Creature::Tick(DeltaTime);
	int decrement = DeltaTime;
	//int qCooltime = player->GetQ_Cooltime();
	//int eCooltime = player->GetE_Cooltime();
	//int rCooltime = player->GetR_Cooltime();
	//int lsCooltime = player->GetLS_Cooltime();

	vector<uint32> Cooltimes = GetCooltimes();
	int qCooltime = Cooltimes[0];
	int eCooltime = Cooltimes[1];
	int rCooltime = Cooltimes[2];
	int lsCooltime = Cooltimes[3];
	vector<uint32>().swap(Cooltimes);


	if (qCooltime > 0)
	{
		SetQ_Cooltime(
			qCooltime > decrement ?
			qCooltime - decrement : 0
		);
	}
	if (eCooltime > 0)
	{
		SetE_Cooltime(
			eCooltime > decrement ?
			eCooltime - decrement : 0
		);
	}
	if (rCooltime > 0)
	{
		SetR_Cooltime(
			rCooltime > decrement ?
			rCooltime - decrement : 0
		);
	}
	if (lsCooltime > 0)
	{
		SetLS_Cooltime(
			lsCooltime > decrement ?
			lsCooltime - decrement : 0
		);
	}
}

void Player::UseSkillQ()
{
	skillCoolTime->set_q_cooltime(Q_COOLTIME);
}

void Player::UseSkillE()
{
	skillCoolTime->set_e_cooltime(E_COOLTIME);
}

void Player::UseSkillR()
{
	skillCoolTime->set_r_cooltime(R_COOLTIME);
}

void Player::UseSkillLS()
{
	skillCoolTime->set_ls_cooltime(LS_COOLTIME);
}

void Player::SetQ_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_q_cooltime(cooltime);
}

void Player::SetE_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_e_cooltime(cooltime);
}

void Player::SetR_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_r_cooltime(cooltime);
}

void Player::SetLS_Cooltime(uint32 cooltime)
{
	GetWriteLock();
	skillCoolTime->set_ls_cooltime(cooltime);
}
