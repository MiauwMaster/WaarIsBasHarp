#include "object.h"

Object::Object(std::string name, std::string description)
{
	Setup(name, description);
}
/// <summary>
/// Set up new object (room, item, pickup, etc)
/// </summary>
/// <param name="name">Name of object</param>
/// <param name="description">Description of object</param>
void Object::Setup(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
}

/// <summary>
/// Set up the location and neigbhours of object
/// </summary>
/// <param name="location">in case of item, location of item</param>
/// <param name="toNorth">object to north</param>
/// <param name="toEast">object to east</param>
/// <param name="toSouth">object to south</param>
/// <param name="toWest">object to west</param>
/// <param name="toUp">object one level up</param>
/// <param name="toDown">object one level down</param>
void Object::SetupNeighbours(Object* location, Object* toNorth, Object* toEast, Object* toSouth, Object* toWest, Object* toUp, Object* toDown, Object* needed)
{
	this->location = location;
	this->toNorth = toNorth;
	this->toEast = toEast;
	this->toSouth = toSouth;
	this->toWest = toWest;
	this->toUp = toUp;
	this->toDown = toDown;
	this->needed = needed;
}