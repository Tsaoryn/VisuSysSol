#include "glimac/Moon.hpp"
#include <math.h>
#include <iostream>

namespace glimac{

    void Moon::drawMoon(float planetDiameter, float t, Camera* camera){
        float scaleValue = _diameter/planetDiameter;
        _ellipse.draw(camera);
        float angle = (t*15.0f);
        glm::vec3 vec = _ellipse.translationVector(angle);
        _drawer.drawPlanet(t, camera, true, false, 1.0f, scaleValue, vec);
    }
    
    void Moon::deleteTextures(){
        _drawer.deleteTextures(false);
    }
}
