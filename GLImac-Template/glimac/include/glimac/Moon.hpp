#pragma once
#include "SphereDrawer.hpp"

#include <iostream>

using namespace std;

namespace glimac {
    class Moon{
    	
        private:
            SphereDrawer _drawer;
            
            Ellipse _ellipse;

            float _aphelion;
            float _perihelion;
            float _eccentricity;
            float _diameter;
            float _inclination;

        public:
            Moon(){}
            Moon(Moon const&){}
            Moon(char* path, std::string pathImg, float majorAxis, float eccentricity, float diameter, float inclination, float planetDiameter, int num): _eccentricity(eccentricity), _diameter(diameter), _inclination(glm::radians(inclination)){
                _aphelion = majorAxis * (1+eccentricity);
                _perihelion = majorAxis * (1-eccentricity);
                
                _ellipse = Ellipse(path,_perihelion, _aphelion, _eccentricity, _inclination, num);
                _drawer = SphereDrawer(path, pathImg, "", planetDiameter, false, false); 
            }
            
            void drawMoon(float planetDiameter, float t, Camera* camera);
            void deleteTextures();
    };
}
