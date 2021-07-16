#pragma once
#include <string>

class Utils {
public:
	const static int stdWidth = 80;
	const static int indent = 7;

public:
	static void printHeader(const std::string& headerText, int width = stdWidth + indent);
	static void drawHorizontalBar(int width, char symbol = '-');
	static void clearScreen();

	static std::string toLower(std::string data);
	static void printInFixedWidth(const std::string& data, int width = stdWidth, int indent = indent);
};