#pragma once
class ObjectUtils
{
public:
	static PlayerPtr CreatePlayer(GameSessionPtr session, message::PlayerType type);
	static message::ObjectInfo toObjectInfo(ObjectPtr objectPtr);
	static message::CreatureInfo toCreatureInfo(CreaturePtr creaturePtr);
	static message::PlayerInfo toPlayerInfo(PlayerPtr playerPtr);
private:
	static atomic<unsigned int> s_idGenerator;
};

