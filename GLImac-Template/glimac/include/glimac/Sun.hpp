#pragma once
#include <glimac/Sphere.hpp>
#include <fstream>
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
            std::vector<Planet*> _planets;
            
            void initVboVao();
            void initTexture();
            void initPlanets(char* path);

        public:
            Sun(char* path, Sphere sphere = Sphere(log10(1391016.0f/2.0f), 32, 16), std::string pathImg = "/assets/textures/SunMap.jpg", float diameter = log10(1391016.0f),float rotation = 25.0f*24):
             _diameter(diameter), _rotation(rotation), _sphere(sphere){
    
                std::cout << log10(1391016.0f) << endl;
                ifstream file("../GLImac-Template/assets/ressources/path.txt");
                std::string subPath;
                getline(file, subPath);
                 
                _imgSun = loadImage(subPath+pathImg);
                FilePath applicationPath(path);
                _programSun = {applicationPath};
                this->initVboVao();
                this->initTexture();
                this->initPlanets(path);
            }
            
            void drawOnePlanet(int numPlanet, float t, Camera* camera);
            void drawSystem(float t, Camera* camera);
            void deleteTextures();
    };
}
