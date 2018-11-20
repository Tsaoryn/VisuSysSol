#include "Parseur.hpp"


namespace glimac{

    void Parseur::readFileArray(const char* filename, list<std::string> *lines){
        ifstream file(filename);
        std::string s;
        
        while(getline(file, s))
            lines->push_back(s);
    }

    std::list<std::array<string,5>> Parseur::splitInArray(const list<std::string> lines){
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
}