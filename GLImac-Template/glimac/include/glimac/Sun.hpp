#pragma once
#include <glimac/Sphere.hpp>
#include <map>
#include "SunProgram.hpp"
#include "Planet.hpp"
#include "Moon.hpp"

namespace glimac {
    class Sun{
        private:
            GLuint _vbo;
            GLuint _vao;
            GLuint _textureSun;
            SunProgram _programSun;
            Sphere _sphere;
            std::unique_ptr<Image> _imgSun;
            float _rotation;
            std::map<string,Planet> _planets;
            
            void initVboVao();
            void initTexture();
            void initPlanets(PlanetProgram programPlanet, MoonProgram programMoon);
        public:
            Sun(SunProgram programSun, PlanetProgram programPlanet, MoonProgram programMoon, Sphere sphere = Sphere(1.0, 32, 16), std::string pathImg = "/home/2ins2/ksadki01/Documents/synthese/GLImac-Template/assets/textures/SunMap.jpg", float rotation = 25.0f):
             _rotation(rotation), _programSun(programSun), _sphere(sphere){
                _imgSun = loadImage(pathImg);
                this->initVboVao();
                this->initTexture();
                this->initPlanets(programPlanet, programMoon);
            }
    };
}
