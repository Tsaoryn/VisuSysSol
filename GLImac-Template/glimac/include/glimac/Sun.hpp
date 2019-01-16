#pragma once
#include <fstream>
#include "Planet.hpp"
#include "SphereDrawer.hpp"
#include "Moon.hpp"

namespace glimac {
    class Sun{
        private:
            float _diameter;
            float _rotation;
            SphereDrawer _drawer;
            std::vector<Planet*> _planets;
            
            void initPlanets(char* path);

        public:
            Sun(char* path, std::string pathImg = "/assets/textures/SunMap.jpg", float diameter = 1391016.0f,float rotation = 25.0f*24):
             _diameter(diameter), _rotation(rotation){
    
                ifstream file("../GLImac-Template/assets/ressources/path.txt");
                std::string subPath;
                getline(file, subPath);
                
                _drawer = SphereDrawer(path, subPath+pathImg, "", _diameter, false, false);
                this->initPlanets(path);
            }
            
            void drawOnePlanet(int numPlanet, float t, Camera* camera);
            void drawSystem(float t, Camera* camera);
            void deleteTextures();
    };
}
