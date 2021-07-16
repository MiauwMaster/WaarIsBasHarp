#include "action.h"
#include "object.h"
#include "utils.h"

#include <string>
#include <iostream>


void initscreen(Object* player)
{
	Utils::clearScreen();
	Utils::printHeader(player->location->name);
}

void moveTo(Object* player, Object* destination)
{
	if (destination != nullptr)
	{
		player->location = destination;
		initscreen(player);
		look(player->location);
	}
	else
	{
		Utils::printInFixedWidth("I can't go there");
	}
}

void look(Object* object)
{
	if (object != nullptr)
	{
		Utils::printInFixedWidth(object->description);
	}
	else 
	{
		Utils::printInFixedWidth("Nothing to see here...");
	}
}
void take(Object* player, Object* toTake)
{
	if (player->location == toTake->location)
	{
		toTake->location = player;
		Utils::printInFixedWidth("Taken " + toTake->name);
	}
	else
		Utils::printInFixedWidth("I can't find that...");
}

void drop(Object* player, Object* toDrop)
{
	if (toDrop->location == player)
	{
		toDrop->location = player->location;
		Utils::printInFixedWidth("Dropped " + toDrop->name);
	}
	else
		Utils::printInFixedWidth("I don't have that...");
}