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
		std::cout << "\t" << "Nothing to see here..." << std::endl;
	}
}
void take(Object* player, std::string name)
{
	std::cout << "\t" << "Can't do that yet..." << std::endl;
}

void drop(Object* player, std::string name)
{
	std::cout << "\t" << "Can't do that yet..." << std::endl;
}