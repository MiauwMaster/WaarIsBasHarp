#include "utils.h"

#include <iostream>
#include <algorithm>
#include <cctype>

#include <stdlib.h>

void Utils::printHeader(const std::string& headerText)
{
	drawHorizontalBar(87);
	std::string head = "| " + headerText + " |";
	std::cout << " " << head << std::endl << " ";
	drawHorizontalBar(head.size());
	std::cout << std::endl;
}

void Utils::drawHorizontalBar(int width, char symbol)
{
	for (int i = 0; i < width; i++)
	{
		std::cout << symbol;
	}
	std::cout << std::endl;
}

void Utils::clearScreen()
{
	std::cout << std::flush;
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) && !defined(__CYGWIN__)
	system("cls");
#else
	system("clear");
#endif
}

std::string Utils::toLower(std::string data)
{
	std::string newString = data;
	std::transform(newString.begin(), newString.end(), newString.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return newString;
}

void Utils::printInFixedWidth(const std::string& data, int width)
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (i != 0 && i % width == 0)
		{
			std::cout << "\n\t";
		}
		std::cout << data[i];
	}
	std::cout << std::endl;
}
