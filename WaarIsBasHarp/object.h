#pragma once
#include <string>

class Object { 
public:
	std::string name;
	std::string description;

	Object* location = nullptr;
	Object* toNorth = nullptr;
	Object* toEast = nullptr;
	Object* toSouth = nullptr;
	Object* toWest = nullptr;
	Object* toUp = nullptr;
	Object* toDown = nullptr;

	Object(std::string name, std::string description);
	void Setup(std::string name, std::string description);
	void SetupNeighbours(Object* location, Object* toNorth, Object* toEast, Object* toSouth, Object* toWest, Object* toUp, Object* toDown);
};