#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <array>

using namespace std;

namespace glimac {
	class Parseur{

		public :
			void readFileArray(const char* filename, list<std::string> lines);
			std::list<std::array<string, 5>> splitInArray(const std::array<std::string, 5> lines);
	};
}