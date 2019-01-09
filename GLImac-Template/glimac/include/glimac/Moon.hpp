#pragma once
#include "MoonProgram.hpp"
#include <glimac/TrackballCamera.hpp>
#include <glimac/Image.hpp>

using namespace std;

namespace glimac {
    class Moon{
    	
        private:
            GLuint _textureMoon;
            MoonProgram _programMoon;
            std::unique_ptr<Image> _imgMoon;
            std::string _name;

            float _majorAxis;
            float _eccentricity;
            float _diameter;
            float _inclination;
            
            void initTexture();

        public:
            Moon(){}
            Moon(Moon const&){}
            Moon(char* path, std::string name, std::string pathImg, float majorAxis, float eccentricity, float diameter, float inclination): _name(name), _majorAxis(majorAxis),_eccentricity(eccentricity), _diameter(diameter), _inclination(inclination){
                FilePath applicationPath(path);
                _programMoon = {applicationPath};
                _imgMoon = loadImage(pathImg);
                initTexture();
            }
            
            std::string getName();
            void drawMoon(float planetDiameter, glm::mat4 ProjMatrix, float nb_vertex, float t, GLuint vao, TrackballCamera* camera);
            void deleteTextures();
    };
}
