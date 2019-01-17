#pragma once
#include <fstream>
#include "Planet.hpp"
#include "SphereDrawer.hpp"
#include "Moon.hpp"

namespace glimac {
    /* classe représentant le soleil */
    class Sun{
        private:
            float _diameter;
            float _rotation;
            SphereDrawer _drawer;
            std::vector<Planet*> _planets;
            // initialise les planètes du systeme et leurs lunes
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
            // dessine une planete en vue planetaire
            void drawOnePlanet(int numPlanet, float t, Camera* camera);
            // dessine le systeme solaire
            void drawSystem(float t, Camera* camera);
            // suprimme les textures de toutes les planetes
            void deleteTextures();
    };
}
