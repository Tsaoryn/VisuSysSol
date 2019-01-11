#pragma once
#include <vector>
#include "common.hpp"
#include "glimac/Camera.hpp"

namespace glimac {

class Ellipse {
    private:
        std::vector<int[3]> vertices;
        float _perihelion;
        float _aphelion;
        float _eccentricity;
        float _inclination;
        
        void initVertices();
    public:
        Ellipse(){}
    
        Ellipse(float perihelion, float aphelion, float eccentricity, float inclination) : _perihelion(perihelion), _aphelion(aphelion), _eccentricity(eccentricity), _inclination(inclination){
            this->initVertices();
        }
        
        void draw(float referenceDiameter, Camera* camera);
    };
}
