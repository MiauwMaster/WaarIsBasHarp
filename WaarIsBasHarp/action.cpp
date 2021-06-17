#include "action.h"
#include "object.h"
#include <string>
#include <iostream>


void moveTo(Object* player, int direction)
{
	if (direction == directNorth && player->location->toNorth != nullptr)
	{
		player->location = player->location->toNorth;
		look(player);
	}
	else if (direction == directEast && player->location->toEast != nullptr)
	{
		player->location = player->location->toEast;
		look(player);
	}
	else if (direction == directSouth && player->location->toSouth != nullptr)
	{
		player->location = player->location->toSouth;
		look(player);
	}
	else if (direction == directWest && player->location->toWest != nullptr)
	{
		player->location = player->location->toWest;
		look(player);
	}
	else if (direction == directUp && player->location->toUp != nullptr)
	{
		player->location = player->location->toUp;
		look(player);
	}
	else if (direction == directDown && player->location->toDown != nullptr)
	{
		player->location = player->location->toDown;
		look(player);
	}
	else
	{
		std::cout << "\tI can't go there" << std::endl;
	}
}

void look(Object* player)
{
	if (player->location != nullptr)
	{
		std::cout << "\tYou see " << player->location->description << std::endl;
	}
	else 
	{
		std::cout << "\tI'm nowhere?!?! HELP!!!!" << std::endl;
	}
}

void look(Object* player, int direction)
{
	if (direction == directNorth && player->location->toNorth != nullptr)
	{
		std::cout << "\tYou see " << player->location->toNorth->description << std::endl;
	}
	else if (direction == directEast && player->location->toEast != nullptr)
	{
		std::cout << "\tYou see " << player->location->toEast->description << std::endl;
	}
	else if (direction == directSouth && player->location->toSouth != nullptr)
	{
		std::cout << "\tYou see " << player->location->toSouth->description << std::endl;
	}
	else if (direction == directWest && player->location->toWest != nullptr)
	{
		std::cout << "\tYou see " << player->location->toWest->description << std::endl;
	}
	else if (direction == directUp && player->location->toUp != nullptr)
	{
		std::cout << "\tYou see " << player->location->toUp->description << std::endl;
	}
	else if (direction == directDown && player->location->toDown != nullptr)
	{
		std::cout << "\tYou see " << player->location->toDown->description << std::endl;
	}
	else
	{
		std::cout << "\tThere is nothing to see there..." << std::endl;
	}
}

void take(Object* player, std::string name)
{
	std::cout << "\tCan't do that yet..." << std::endl;
}

void drop(Object* player, std::string name)
{
	std::cout << "\tCan't do that yet..." << std::endl;
}