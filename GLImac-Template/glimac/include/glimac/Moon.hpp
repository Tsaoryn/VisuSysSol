#pragma once
#include "MoonProgram.hpp"
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
            float _orbitalInclination;
            
            void initTexture();
        public:
            Moon(Moon const&);
            
            Moon(std::string name,std::string pathImg, float ellipse, float diameter, float orbitalInclination, MoonProgram programMoon):
            _name(name), _ellipse(ellipse), _diameter(diameter), _orbitalInclination(orbitalInclination), _programMoon(programMoon){
                _imgMoon = loadImage(pathImg);
                initTexture();
            }
            
            std::string getName();
    };
}
