#include "glimac/Planet.hpp"
#include <iostream>

namespace glimac{
    
    void Planet::drawPlanet(float sunDiameter, float t, Camera* camera){
        float scaleValue = _diameter/sunDiameter;
        _ellipse.draw(camera);
        float angle = (t*1000/_orbitalPeriod);
        glm::vec3 vec = _ellipse.translationVector(angle);
        
        _drawer.drawPlanet(t, camera, true, _extra, _lengthDays, scaleValue, vec);
    }

    
    void Planet::drawPlanetAlone(float sunDiameter, float t, Camera* camera){
        float scaleValue = log10(_diameter/2.0f)/log10(sunDiameter/2.0f);
        _drawer.drawPlanet(t, camera, false, _extra, _lengthDays, scaleValue);
        for(auto moon : _moons)
            moon->drawMoon(_diameter, t, camera);
	}
    
    void Planet::deleteTextures(){
        _drawer.deleteTextures(_extra);
        for(auto moon : _moons)
            moon->deleteTextures();
    }
}
