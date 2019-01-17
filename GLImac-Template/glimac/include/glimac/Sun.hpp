#pragma once
#include <fstream>
#include "Planet.hpp"
#include "SphereDrawer.hpp"
#include "Moon.hpp"
#include <memory>

namespace glimac {
    /* classe représentant le soleil */
    class Sun{
        private:
            float _diameter;
            float _rotation;
            SphereDrawer _drawer;
            std::vector<std::shared_ptr<Planet>> _planets;
            // initialise les planètes du systeme et leurs lunes
            void initPlanets(char* path, std::string subPath);

        public:
            Sun(char* path, std::string subPath,std::string pathImg = "/assets/textures/SunMap.jpg", float diameter = 1391016.0f,float rotation = 25.0f*24):
             _diameter(diameter), _rotation(rotation){
                _drawer = SphereDrawer(path, subPath+pathImg, "", _diameter, false, false, false);
                this->initPlanets(path,subPath);
            }
            // dessine une planete en vue planetaire
            void drawOnePlanet(int numPlanet, float t, std::shared_ptr<Camera> camera);
            // dessine le systeme solaire
            void drawSystem(float t, std::shared_ptr<Camera> camera);
            // suprimme les textures de toutes les planetes
            void deleteTextures();
    };
}
