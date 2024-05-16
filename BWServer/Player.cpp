#include "pch.h"
#include "Player.h"

Player::Player()
{
	player_info = new message::PlayerInfo();
	player_info->set_player_type(message::PLAYER_TYPE_NONE);
}

Player::~Player()
{
	delete player_info;
}
