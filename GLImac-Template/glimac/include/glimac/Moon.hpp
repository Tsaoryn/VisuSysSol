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
            float _inclination;
            
            void initTexture();
        public:
            Moon(Moon const&){}
            
            Moon(){}
            
            Moon(char* path, std::string name,std::string pathImg, float ellipse, float diameter, float inclination):
            _name(name), _ellipse(ellipse), _diameter(diameter), _inclination(inclination){
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
