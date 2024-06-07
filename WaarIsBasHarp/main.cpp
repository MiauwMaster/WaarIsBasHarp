#include "action.h"
#include "main.h"
#include "object.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <tuple>
#include <vector>

std::map<std::string, Object*> objects;
std::string intro;
std::vector<std::string> header;

bool initializeMap(std::string fileName)
{
	objects.insert(std::pair<std::string, Object*>("NONE", nullptr));
	std::string filename = ".\\" +fileName;
	std::ifstream input(filename);
	if (!input.good())
	{
		std::cout << "Loading file "<< filename << " went wrong" << std::endl;
		return false;
	}
	std::string buffer;
	std::string id;
	std::string name;
	std::string description;
	std::string location;
	std::string toNorth;
	std::string toEast;
	std::string toSouth;
	std::string toWest;
	std::string toUp;
	std::string toDown;
	std::string needed;
	while (input >> buffer)
	{
		if (buffer == "START_INTRO")
		{
			input.ignore();
			std::getline(input, intro);
		}

		else if (buffer == "START_HEADER")
		{
			std::string tmp;
			input.ignore();

			for (size_t i = 0; i < 5; i++)
			{
				std::getline(input, tmp);
				header.push_back(tmp);
			}
		}

		else if (buffer == "START_ROOM")
		{
			input >> id;

			input.ignore();
			std::getline(input, name);
			std::getline(input, description);
			objects.insert(std::pair<std::string, Object*>(id, new Object(name, description)));
		}

		else if (buffer == "END_ROOM" || buffer == "END_NEIGHBOUR") {
			// clear strings
			id.clear();
			name.clear();
			description.clear();
			location.clear();
			toNorth.clear();
			toEast.clear();
			toSouth.clear();
			toWest.clear();
			toUp.clear();
			toDown.clear();
			needed.clear();
		}

		// setup neighbours
		else if (buffer == "START_NEIGHBOUR")
		{
			input >> id;

			input >> buffer; // location
			input >> location;

			input >> buffer; // tonorth
			input >> toNorth;

			input >> buffer; // toeast
			input >> toEast;

			input >> buffer; // tosouth
			input >> toSouth;

			input >> buffer; // towest
			input >> toWest;

			input >> buffer; // toup
			input >> toUp;

			input >> buffer; // todown
			input >> toDown;

			input >> buffer; // needed
			input >> needed;

			// setup neighbours
			objects[id]->SetupNeighbours(objects[location], objects[toNorth], objects[toEast], objects[toSouth], objects[toWest], objects[toUp], objects[toDown], objects[needed]);
		}
	}
	return true;
}

int getParseInput()
{
	std::string input;	
	std::string verb;
	std::string noun;

	std::cout << "\n\t> ";
	std::getline(std::cin, input);
	std::cout << std::endl;

	std::stringstream ss(input);
	std::string temp;
	int numWords = 0;
	while (ss >> temp)
	{
		if (numWords == 0) 
		{
			verb = Utils::toLower(temp);
			numWords++;
		}		
		else if (numWords == 1)
		{
			noun += Utils::toLower(temp);
			numWords++;
		}
		else
		{
			noun += " ";
			noun += Utils::toLower(temp);
			numWords++;
		}
	}

	
	//go somewhere
	if (verb == "go")
	{
		if (noun == "north" || noun == "n")
		{
			moveTo(objects["player"], objects["player"]->location->toNorth);
		}
		else if (noun == "east" || noun == "e")
		{
			moveTo(objects["player"], objects["player"]->location->toEast);
		}
		else if (noun == "south" || noun == "s")
		{
			moveTo(objects["player"], objects["player"]->location->toSouth);
		}
		else if (noun == "west" || noun == "w")
		{
			moveTo(objects["player"], objects["player"]->location->toWest);
		}
		else if (noun == "up" || noun == "u")
		{
			moveTo(objects["player"], objects["player"]->location->toUp);
		}
		else if (noun == "down" || noun == "d")
		{
			moveTo(objects["player"], objects["player"]->location->toDown);
		}
		else
		{
			Utils::printInFixedWidth("go where?");
		}
	}
	//look at something
	else if (verb == "look") 
	{
		if (noun == "")
		{
			look(objects["player"]);
			for (auto& item : objects)
			{
				if (item.second != nullptr && item.second->location == objects["player"])
				{
					look(item.second);
				}
			}
		}
		else if (noun == "around")
		{
			look(objects["player"]->location);
			for (auto& item : objects)
			{
				if (item.second != nullptr && item.second->location == objects["player"]->location and item.first != "player")
				{
					look(item.second);
				}
			}
		}
		else if (noun == "north" || noun == "n")
		{
			look(objects["player"]->location->toNorth);
		}
		else if (noun == "east" || noun == "e")
		{
			look(objects["player"]->location->toEast);
		}
		else if (noun == "south" || noun == "s")
		{
			look(objects["player"]->location->toSouth);
		}
		else if (noun == "west" || noun == "w")
		{
			look(objects["player"]->location->toWest);
		}
		else if (noun == "up" || noun == "u")
		{
			look(objects["player"]->location->toUp);
		}
		else if (noun == "down" || noun == "d")
		{
			look(objects["player"]->location->toDown);
		}
		else
		{
			Utils::printInFixedWidth("look where?");
		}

	}
	//pick stuff up
	else if (verb == "take")
	{
		if (noun != "")
		{
			bool found = false;
			for (auto& item: objects) {
				if (item.second != nullptr && item.second->name == noun)
				{
					found = true;
					take(objects["player"], objects[item.first]);
					break;
				}
			}
			if (!found)
			{
				Utils::printInFixedWidth("take what?");
			}
		}
		else
		{
			Utils::printInFixedWidth("take what?");
		}
	}
	//drop stuff
	else if (verb == "drop")
	{
		if (noun != "")
		{
			bool found = false;
			for (auto& item: objects) {
				if (item.second != nullptr && item.second->name == noun)
				{
					found = true;
					drop(objects["player"], objects[item.first]);
					break;
				}
			}
			if (!found)
			{
				Utils::printInFixedWidth("drop what?");
			}
		}
		else
		{
			Utils::printInFixedWidth("drop what?");
		}
	}
	//quit
	else if (verb == "quit" || verb == "exit")
	{
		Utils::clearScreen();
		Utils::printInFixedWidth("Goodbye!");
		return false;
	}
	//get help
	else if (verb == "help")
	{
		Utils::printInFixedWidth("You can look at where you are now by typing \'look\'");
		Utils::printInFixedWidth("To see if there's anything nearby you can \'look around\'");
		Utils::printInFixedWidth("you can also look in a specific directon by typing, for example, \'look north\'");
		Utils::printInFixedWidth("the possible directions are (n)orth, (e)ast, (s)outh, (w)est, (u)p and (d)own.");
		Utils::printInFixedWidth("If you spot somewhere you like to go you can do so by typing \'go\' plus the direction, for example type \'go north\'");
		Utils::printInFixedWidth("You can take and drop items by typing \'take item\' and \'drop item\', for example \'take coin\'");
		Utils::printInFixedWidth("to stop, simply type \'quit\' or \'exit\', you will lose all progress though..");
	}
	else
	{
		Utils::printInFixedWidth("what now?");
	}

	return true;
}

int main()
{
	Utils::clearScreen();

	if (!initializeMap("bigmap.mapfile"))
	{
		Utils::printInFixedWidth("Map loading went wrong!");
		return false;
	}
	
	initscreen(objects["player"]);


	for (size_t i = 0; i < header.size(); i++)
	{
		Utils::printInFixedWidth(header[i]);
	}
	Utils::printInFixedWidth("\n");
	Utils::printInFixedWidth(intro);
	Utils::printInFixedWidth("\n");
	look(objects["player"]->location);
	Utils::printInFixedWidth("\n");
	Utils::printInFixedWidth("Now what...");
	while (getParseInput());
}