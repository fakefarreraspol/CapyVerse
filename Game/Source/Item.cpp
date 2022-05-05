#include "Item.h"
#include "Entity.h"

Item::Item(uint32 id, iPoint bounds, const char* name) : Entity(EntityType::PLAYER, id, name, position)
{

}

Item::~Item()
{

}