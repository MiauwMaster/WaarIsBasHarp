#pragma once
#include <string>

class Utils {

public:
	static void printHeader(const std::string& headerText);
	static void drawHorizontalBar(int width, char symbol = '-');
	static void clearScreen();

	static std::string toLower(std::string data);
	static void printInFixedWidth(const std::string& data, int width = 80);
};