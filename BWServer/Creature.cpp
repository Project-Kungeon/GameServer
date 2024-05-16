#include "pch.h"
#include "Creature.h"

Creature::Creature()
{
	objectInfo->set_object_type(message::OBJECT_TYPE_CREATURE);
	creatureInfo = new message::CreatureInfo();
}

Creature::~Creature()
{
	delete creatureInfo;
}
