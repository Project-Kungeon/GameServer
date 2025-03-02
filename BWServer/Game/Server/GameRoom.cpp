#include "pch.h"
#include "GameRoom.h"

void GameRoom::init(boost::asio::io_context& io_context)
{
	for (int i = 0; i < 3; i++)
	{
		GRoom[i] = std::make_shared<GameRoom>(io_context);
	}
}

void GameRoom::HandleTick(uint32 DeltaTime)
{
	Room::HandleTick(DeltaTime);
	if (IsRoundPlaying)
	{
		const system_clock::time_point now = system_clock::now();
		if (round_end_tp < now)
		{
			IsRoundPlaying = false;
			BroadcastRoundEnd(game::round::S_Round_EndInfo_EndReasonType_ROUND_TIME_OVER);
		}

		// 모두 죽고, 카운트 다운 상태가 아닐 경우
		if (IsPlayerAllDead() && !IsCountdown)
		{
			IsCountdown = true;
			BroadcastRoundGameOverCountdown(5);
		}

	}

	
}

bool GameRoom::HandleEnterPlayer(PlayerPtr player)
{
	bool result = Room::HandleEnterPlayer(player);

	if (result)
	{
		Number_of_Players_Remaining++;
	}
	return result;
}

bool GameRoom::HandleLeavePlayer(PlayerPtr player)
{
	bool result = Room::HandleLeavePlayer(player);

	if (result)
	{
		Number_of_Players_Remaining--;
	}
	return result;
}

bool GameRoom::SpawnMonster(MonsterPtr monster)
{
	bool result = Room::SpawnMonster(monster);
	if (result)
	{
		Number_of_Monsters_Remaining++;
	}
	return result;
}

void GameRoom::HandleDeath(CreaturePtr creature)
{
	switch (creature->GetCreatureType())
	{
	case message::CREATURE_TYPE_PLAYER:
		Number_of_Players_Remaining--;
		break;
	case message::CREATURE_TYPE_MONSTER:
		Number_of_Monsters_Remaining--;
		break;
	}

}

void GameRoom::RoundStart()
{
	const system_clock::time_point now = system_clock::now();
	const system_clock::time_point round_end_time = now + minutes(3);
	round_end_tp = round_end_time;
	IsRoundPlaying = true;
	BroadcastRoundStart();

}

void GameRoom::BroadcastRoundStart()
{
	game::round::S_Round_StartInfo pkt;
	Broadcast(pkt, message::HEADER::ROUND_START_RES, 0);
}

void GameRoom::BroadcastRoundTime()
{
}

void GameRoom::BroadcastRoundEnd(game::round::S_Round_EndInfo_EndReasonType type)
{
	switch (type)
	{
	case game::round::S_Round_EndInfo_EndReasonType_ROUND_TIME_OVER:
		spdlog::info("Round Time Over!");
		break;
	case game::round::S_Round_EndInfo_EndReasonType_PLAYER_ALL_DEAD:
		spdlog::info("Player all dead... Game Over!");
		break;

	}

	game::round::S_Round_EndInfo pkt;
	pkt.set_type(type);

	Broadcast(pkt, message::HEADER::ROUND_END_RES, 0);

}

void GameRoom::BroadcastRoundGameOverCountdown(int count)
{
	spdlog::info("Round GameOver Countdown... {}", count);
	game::round::S_Round_GameOver_Countdown pkt;
	pkt.set_count(count);
	const size_t requiredSize = PacketUtil::RequiredSize(pkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::ROUND_GAMEOVER_COUNTDOWN_RES, pkt);

	if (count > 0)
	{
		DoTimer(1000, &GameRoom::BroadcastRoundGameOverCountdown, count - 1);
	}
	else
	{
		IsRoundPlaying = false;
		BroadcastRoundEnd(game::round::S_Round_EndInfo_EndReasonType_PLAYER_ALL_DEAD);
	}
	

}
