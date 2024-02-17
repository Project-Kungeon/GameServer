#pragma once
class ObjectUtils
{
public:
	static PlayerPtr CreatePlayer(GameSessionPtr session);

private:
	static atomic<unsigned int> s_idGenerator;
};

