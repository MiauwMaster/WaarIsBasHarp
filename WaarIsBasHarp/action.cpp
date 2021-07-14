#include "action.h"
#include "object.h"
#include "utils.h"

#include <string>
#include <iostream>


void moveTo(Object* player, Object* destination)
{
	if (destination != nullptr)
	{
		player->location = destination;
		Utils::clearScreen();
		Utils::printHeader(player->location->name);
		look(player->location);
	}
	else
	{
		std::cout << "\tI can't go there" << std::endl;
	}
}

void look(Object* object)
{
	if (object != nullptr)
	{
		Utils::printInFixedWidth("\t" + object->description);
	}
	else 
	{
		Utils::printInFixedWidth("\tNothing to see here...");
	}
}
void take(Object* player, Object* toTake)
{
	if (player->location == toTake->location)
	{
		toTake->location = player;
		Utils::printInFixedWidth("\tTaken " + toTake->name);
	}
	else
		Utils::printInFixedWidth("\tI can't find that...");
}

void drop(Object* player, Object* toDrop)
{
	if (toDrop->location == player)
	{
		toDrop->location = player->location;
		Utils::printInFixedWidth("\tDropped " + toDrop->name);
	}
	else
		Utils::printInFixedWidth("\tI don't have that...");
}