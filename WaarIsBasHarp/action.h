#pragma once
#include "object.h"
#include <string>

const int directNorth = 1;
const int directEast = 2;
const int directSouth = 3;
const int directWest = 4;
const int directUp = 5;
const int directDown = 6;


void moveTo(Object* player, int direction);
void look(Object* player);
void look(Object* player, int direction);
void take(Object* player, std::string name);
void drop(Object* player, std::string name); 