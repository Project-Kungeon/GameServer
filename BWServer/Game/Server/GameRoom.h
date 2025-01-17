#pragma once
#include "Room.h"
#include "GameRound.pb.h"

using namespace std::chrono;

class GameRoom :
    public Room
{
public:
    GameRoom(boost::asio::io_context& io_context)
        : Room(io_context)
    {}

public:
    static void init(boost::asio::io_context& io_context);
    virtual void HandleTick(uint32 DeltaTime) override;
    virtual bool HandleEnterPlayer(PlayerPtr player) override;
    virtual bool HandleLeavePlayer(PlayerPtr player) override;
    virtual bool SpawnMonster(MonsterPtr monster) override;

    virtual void HandleDeath(CreaturePtr creature) override;

    void RoundStart();
    bool IsPlayerAllDead() { return IsRoundPlaying && Number_of_Players_Remaining == 0; }
    bool IsMoonsterAllDead() { return IsRoundPlaying && Number_of_Monsters_Remaining == 0; }


    // Broadcast
public:
    void BroadcastRoundStart();
    void BroadcastRoundTime();
    void BroadcastRoundEnd(game::round::S_Round_EndInfo_EndReasonType type);
    void BroadcastRoundGameOverCountdown(int count);

private:
    int Number_of_Monsters_Remaining = 0;
    int Number_of_Players_Remaining = 0;

    bool IsCountdown = false;

    int64 remaining_seconds;
    system_clock::time_point round_end_tp;

    bool IsRoundPlaying = false;

};

