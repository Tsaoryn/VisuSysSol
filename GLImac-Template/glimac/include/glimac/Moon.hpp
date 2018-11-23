#pragma once
#include "MoonProgram.hpp"
#include <glimac/Parseur.hpp>
#include <glimac/Image.hpp>

using namespace std;

namespace glimac {
    class Moon{
    	
        private:
            GLuint _textureMoon;
            MoonProgram _programMoon;
            std::unique_ptr<Image> _imgMoon;
            
            std::string _name;
            float _ellipse;
            float _diameter;
            float _inclination;
            
            void initTexture();
            void initMoon(std::string name);

        public:
            Moon(){}
            Moon(Moon const&){}
            Moon(char* path, std::string name) : _name(name){
                initMoon(name);

                FilePath applicationPath(path);
                _programMoon = {applicationPath};

                std:string subPath = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template";
                std::string pathImg = subPath+"/assets/textures/MoonMap.jpg";
                _imgMoon = loadImage(pathImg);

                initTexture();
            }
            
            std::string getName();
            void drawMoon();
            void deleteTextures();
    };
}
