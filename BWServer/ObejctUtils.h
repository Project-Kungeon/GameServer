#pragma once
class ObejctUtils
{
public:
	PlayerPtr CreatePlayer(GameSessionPtr session);

private:
	static atomic<unsigned int> s_idGenerator;
};

