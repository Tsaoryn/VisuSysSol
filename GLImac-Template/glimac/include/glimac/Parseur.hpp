#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <array>

using namespace std;

namespace glimac {

	extern list<std::string> readFileList(const char* filename);
	extern std::list<std::array<string,5>> splitMoon();
	extern std::list<std::array<string,9>> splitPlanet();
	extern std::list<std::string> splitMoonPlanet(string name);
}
