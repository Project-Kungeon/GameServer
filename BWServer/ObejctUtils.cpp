#include "pch.h"
#include "ObejctUtils.h"

atomic<unsigned int> ObejctUtils::s_idGenerator = 1;

PlayerPtr ObejctUtils::CreatePlayer(GameSessionPtr session)
{
	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	PlayerPtr player = boost::make_shared<Player>();
	player->objectInfo->set_object_id(newId);
	player->posInfo->set_object_id(newId);
	
	player->session = session;
	


	return PlayerPtr();
}
