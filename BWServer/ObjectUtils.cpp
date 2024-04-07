#include "pch.h"
#include "ObjectUtils.h"

atomic<unsigned int> ObjectUtils::s_idGenerator = 1;

PlayerPtr ObjectUtils::CreatePlayer(GameSessionPtr session)
{
	// Generate ID
	const unsigned int newId = s_idGenerator.fetch_add(1);

	PlayerPtr player = std::make_shared<Player>();
	player->objectInfo->set_object_id(newId);
	player->posInfo->set_object_id(newId);
	
	player->session = session;
	session->player.store(player);

	return player;
}
