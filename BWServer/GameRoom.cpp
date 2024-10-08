#include "pch.h"
#include "GameRoom.h"

void GameRoom::HandleTick(uint32 DeltaTime)
{
	Room::HandleTick(DeltaTime);
	if (IsRoundPlaying > 0)
	{
		remaining_seconds -= DeltaTime;
		if (remaining_seconds <= 0)
		{
			IsRoundPlaying = false;
			
			BroadcastRoundEnd(game::round::S_Round_EndInfo_EndReasonType_ROUND_TIME_OVER);
		}
	}

	
}

void GameRoom::BroadcastRoundStart()
{
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
	}

	game::round::S_Round_EndInfo pkt;
	pkt.set_type(type);
	const size_t requiredSize = PacketUtil::RequiredSize(pkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	//PacketUtil::Serialize(sendBuffer, message::HEADER::RAMPAGE_EARTHQUAKE_RES, pkt);
	Broadcast(sendBuffer, 0);

}
