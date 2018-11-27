#include "glimac/Parseur.hpp"


namespace glimac{

    
    extern list<std::string> readFileList(const char* filename){
        list<std::string> lines = {};

        ifstream file(filename);
        std::string s;
        
        while(getline(file, s))
            lines.push_back(s);

        return lines;
    }
    /*
    extern std::list<std::array<string,5>> splitMoon(){
        list<std::string> lines = readFileList("../../assets/ressources/Satellites.txt");

        std::list<std::array<string,5>> array ;
        std::array<string,5> parse;
        std::string tmp ;
        int i ;
        
        for(std::string line : lines){
            std::stringstream ss(line);
            i = 0 ;
            
            while(ss >> tmp && i < 5){
                parse[i] = tmp;
                i++;
            }
            
            array.push_back(parse);
        }

        return array ;
    }

    extern std::list<std::array<string,9>> splitPlanet(){
        list<std::string> lines = readFileList("../../assets/ressources/Planets.txt");

        std::list<std::array<string,9>> array ;
        std::array<string,9> parse;
        std::string tmp ;
        int i ;
        
        for(std::string line : lines){
            std::stringstream ss(line);
            i = 0 ;
            
            while(ss >> tmp && i < 9){
                parse[i] = tmp;
                i++;
            }
            
            array.push_back(parse);
        }

        return array ;
    }
    */

    extern std::list<std::string> splitMoonPlanet(string name){
        list<std::string> lines = readFileList("../../assets/ressources/SatPlanets.txt");
        list<std::string> moons;

        for(string tmp : lines){
            list<std::string> line;
            string delimiter = " ";
            size_t pos = 0;
            string s;

            while ((pos = tmp.find(delimiter)) != std::string::npos) {
                s = tmp.substr(0, pos);
                line.push_back(s);
                tmp.erase(0, pos + delimiter.length());
            }

            list<string>::iterator it;
            it = line.begin();
            if(*it == name)
                for(it = ++line.begin() ; it != line.end() ; it++)
                    moons.push_back(*it);
        }

        return moons;
    }
}