#include "action.h"
#include "main.h"
#include "object.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <tuple>

std::map<std::string, Object*> objects;
std::string intro;

bool initializeMap()
{
	objects.insert(std::pair<std::string, Object*>("NONE", nullptr));
	std::string filename = "map.mapfile";
	std::ifstream input(filename);
	if (!input.good())
	{
		std::cout << "\tLoading file "<< filename << " went wrong" << std::endl;
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
	while (input >> buffer)
	{
		if (buffer == "START_INTRO")
		{
			input.ignore();
			getline(input, intro);
		}

		if (buffer == "START_ROOM")
		{
			input >> id;

			input.ignore();
			getline(input, name);
			getline(input, description);
			objects.insert(std::pair<std::string, Object*>(id, new Object(name, description)));
		}

		if (buffer == "END_ROOM" || buffer == "END_NEIGHBOUR") {
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
		}

		// setup neighbours
		if (buffer == "START_NEIGHBOUR")
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

			// setup neighbours
			objects[id]->SetupNeighbours(objects[location], objects[toNorth], objects[toEast], objects[toSouth], objects[toWest], objects[toUp], objects[toDown]);
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
			noun = Utils::toLower(temp);
			numWords++;
		}
	}

	//quit
	if (verb == "quit" || verb == "exit")
	{
		Utils::clearScreen();
		std::cout << "\tGoodbye!" << std::endl << std::endl << std::endl;
		return false;
	}
	//get help
	if (verb == "help") 
	{
		std::cout << "\tYou can look at where you are now by typing \'look\'" << std::endl
			<< "\tyou can also look in a specific directon by typing, for example, \'look north\'" << std::endl
			<< "\tthe possible directions are north, east, souht, west, up and down." << std::endl
			<< "\tIf you spot somewhere you like to go you can do so by typing \'go\' plus the direction, for example type \'go north\'" << std::endl
			<< "\tto stop, simply type quit or exit, you will lose all progress though.." << std::endl << std::endl;
	}
	//go somewhere
	else if (verb == "go")
	{
		if (noun == "north")
		{
			moveTo(objects["player"], objects["player"]->location->toNorth);
		}
		else if (noun == "east")
		{
			moveTo(objects["player"], objects["player"]->location->toEast);;
		}
		else if (noun == "south")
		{
			moveTo(objects["player"], objects["player"]->location->toSouth);
		}
		else if (noun == "west")
		{
			moveTo(objects["player"], objects["player"]->location->toWest);
		}
		else if (noun == "up")
		{
			moveTo(objects["player"], objects["player"]->location->toUp);
		}
		else if (noun == "down")
		{
			moveTo(objects["player"], objects["player"]->location->toDown);
		}
		else
		{
			std::cout << "\tgo where?" << std::endl;
		}
	}
	//look at something
	else if (verb == "look") 
	{
		if (noun == "")
		{
			look(objects["player"]);
		}
		else if (noun == "around") 
		{
			look(objects["player"]->location);
		}
		else if (noun == "north")
		{
			look(objects["player"]->location->toNorth);
		}
		else if (noun == "east")
		{
			look(objects["player"]->location->toEast);
		}
		else if (noun == "south")
		{
			look(objects["player"]->location->toSouth);
		}
		else if (noun == "west")
		{
			look(objects["player"]->location->toWest);
		}
		else if (noun == "up")
		{
			look(objects["player"]->location->toUp);
		}
		else if (noun == "down")
		{
			look(objects["player"]->location->toDown);
		}
		else
		{
			std::cout << "\tlook where?" << std::endl;
		}

	}
	//pick stuff up
	else if (verb == "take")
	{
		if (noun != "")
		{
			take(objects["player"], noun);
		}
		else
		{
			std::cout << "\ttake what?" << std::endl;
		}
	}
	//drop stuff
	else if (verb == "drop")
	{
		if (noun != "")
		{
			drop(objects["player"], noun);
		}
		else
		{
			std::cout << "\tdrop what?" << std::endl;
		}
	}
	else
	{
		std::cout << "\twhat now?";
	}

	return true;
}

int main()
{
	Utils::clearScreen();
	
	if (!initializeMap())
	{
		std::cout << "\tMap loading went wrong!" << std::endl;
		return false;
	}
	
	Utils::printHeader(objects["player"]->location->name);

	std::cout << "\t" << "-------------------------------------------------------------------------------" << std::endl
		<< "\t" << "-------------------------| Welcome to TextAdventure! |-------------------------" << std::endl
		<< "\t" << "-------------------------|      Truly original!      |-------------------------" << std::endl
		<< "\t" << "-------------------------|          amazing          |-------------------------" << std::endl
		<< "\t" << "-------------------------------------------------------------------------------" << std::endl << std::endl 
		<< "\tAre you ready to begin ? You better...." << std::endl << std::endl << std::endl;

	Utils::printInFixedWidth("\t" + intro);

	std::cout << "\tNow what..." << std::endl << std::endl;

	while (getParseInput());
}