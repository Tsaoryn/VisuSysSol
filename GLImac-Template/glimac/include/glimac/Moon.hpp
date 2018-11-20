#pragma once
#include "MoonProgram.hpp"
#include "Parseur.hpp"
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
            Moon(char* path, std::string name, std::string pathImg) : _name(name){
                initMoon(name);

                FilePath applicationPath(path);
                _programMoon = {applicationPath};
                _imgMoon = loadImage(pathImg);
                initTexture();
            }
            
            std::string getName();
            void drawMoon();
            void deleteTextures();
    };
}
