#pragma once
#include "Moon.hpp"
#include "SphereDrawer.hpp"
#include <list>
#include <memory>

namespace glimac {
    /* classe qui représente une planète */
    class Planet{
        private:
            std::list<std::shared_ptr<Moon>> _moons;
            Ellipse _ellipse;
            
            SphereDrawer _drawer;
                        
            bool _extra;
            bool _rings;
            float _aphelion;
            float _perihelion;
            float _eccentricity;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;

        public:
          	Planet(){}
          	Planet(Planet const&){}
            Planet(char* path, std::string pathImg, std::string pathImg2, std::list<std::shared_ptr<Moon>> moons, bool extra, bool rings, float aphelion, float perihelion, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination, float eccentricity, int num, float radiusRing, float sunDiameter):
            _moons(moons),_aphelion(aphelion), _perihelion(perihelion), _diameter(diameter), _rings(rings), _extra(extra),_orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(glm::radians(orbitalInclination)), _eccentricity(eccentricity){
                
                _ellipse = Ellipse(path,_perihelion, _aphelion, _eccentricity, _orbitalInclination, num);
                _drawer = SphereDrawer(path, pathImg, pathImg2, sunDiameter, rings, extra);
            }
            
            // dessine la planete sur le système solaire
            void drawPlanet(float sunDiameter, float t, std::shared_ptr<Camera> camera);
            // dessine la planète en vue planétaire
            void drawPlanetAlone(float sunDiameter, float t, std::shared_ptr<Camera> camera);
            // suprime la texture liée à la planete et ses lunes
            void deleteTextures();
    };
}
