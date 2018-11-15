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
            float _diameter;
            float _rotation;
            std::list<Planet*> _planets;
            
            void initVboVao();
            void initTexture();
            void initPlanets(char* path);

        public:
            Sun(char* path, Sphere sphere = Sphere(1.0, 32, 16), std::string pathImg = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template/assets/textures/SunMap.jpg", float diameter = 1391016.0f,float rotation = 25.0f*24):
             _diameter(diameter), _rotation(rotation), _sphere(sphere){
                _imgSun = loadImage(pathImg);
                FilePath applicationPath(path);
                _programSun = {applicationPath};
                this->initVboVao();
                this->initTexture();
                this->initPlanets(path);
            }
            
            void drawSystem(float t);
            void deleteTextures();
    };
}
