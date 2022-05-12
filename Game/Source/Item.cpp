#include "Item.h"

Item::Item(uint32 id, iPoint position, const char* name, ItemType type) : Entity(EntityType::ITEM, id, name , position)
{
}
