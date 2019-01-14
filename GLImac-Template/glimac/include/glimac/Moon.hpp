#pragma once
#include "MoonProgram.hpp"
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Ellipse.hpp>
#include <glimac/Image.hpp>

#include <iostream>

using namespace std;

namespace glimac {
    class Moon{
    	
        private:
            GLuint _textureMoon;
            MoonProgram _programMoon;
            std::unique_ptr<Image> _imgMoon;
            std::string _name;
            Ellipse _ellipse;

            float _aphelion;
            float _perihelion;
            float _eccentricity;
            float _diameter;
            float _inclination;
            
            void initTexture();

        public:
            Moon(){}
            Moon(Moon const&){}
            Moon(char* path, std::string name, std::string pathImg, float majorAxis, float eccentricity, float diameter, float inclination, float planetDiameter, int num): _name(name),_eccentricity(eccentricity), _diameter(log10(diameter)), _inclination(glm::radians(inclination)){
                FilePath applicationPath(path);
                _aphelion = majorAxis * (1+eccentricity);
                _perihelion = majorAxis * (1-eccentricity);
                _ellipse = Ellipse(path,_perihelion, _aphelion, _eccentricity, _inclination, num);
                _programMoon = {applicationPath};
                _imgMoon = loadImage(pathImg);
                initTexture();
            }
            
            std::string getName();
            void drawMoon(float planetDiameter, glm::mat4 ProjMatrix, float nb_vertex, float t, GLuint vao, Camera* camera);
            void deleteTextures();
    };
}
