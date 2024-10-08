#pragma once
#include "Room.h"
class GameRoom :
    public Room
{
public:
    virtual void HandleTick(uint32 DeltaTime) override;

public:
    void BroadcastRoundStart();
    void BroadcastRoundTime();
    void BroadcastRoundEnd();

private:

    int Number_of_Monsters_Remaining;
    int Number_of_Players_Remaining;

    int64 remaining_seconds;

};

