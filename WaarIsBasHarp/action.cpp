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
		if (hasNeeded(player, destination))
		{
			player->location = destination;
			initscreen(player);
			look(player->location);
		}
		else
		{
			Utils::printInFixedWidth(std::string("You need a  to go there...").insert(11, destination->needed->name));
		}
	}
	else
	{
		Utils::printInFixedWidth("I can't go there");
	}
}

bool hasNeeded(Object* player, Object* destination)
{
	if (destination->needed == nullptr || destination->needed->location == player)
	{
		return true;
	}
	else
	{
		return false;
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
	if (toTake == player)
	{
		Utils::printInFixedWidth("I can't take myself... Weirdo...");
	}
	else if (player->location == toTake->location)
	{
		toTake->location = player;
		Utils::printInFixedWidth("I'll take that " + toTake->name);
	}
	else
		Utils::printInFixedWidth("I can't find that...");
}

void drop(Object* player, Object* toDrop)
{
	if (toDrop == player)
	{
		Utils::printInFixedWidth("I'll never drop myself!");
	}
	else if (toDrop->location == player)
	{
		toDrop->location = player->location;
		Utils::printInFixedWidth("Well, there goes that " + toDrop->name);
	}
	else
		Utils::printInFixedWidth("I don't have that...");
}