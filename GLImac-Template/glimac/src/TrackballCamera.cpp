#include "glimac/TrackballCamera.hpp"

namespace glimac{
    void TrackballCamera::moveFront(float delta){
        _m_fDistance-=delta;
         if(_m_fDistance<0)
            _m_fDistance = 0;
    }
    
    void TrackballCamera::rotateUp(float degrees){
        _m_fAngleX-=degrees/20.0f;
    }
    
    void TrackballCamera::rotateLeft(float degrees){
        _m_fAngleY-=degrees/20.0f;
    }
    
    glm::mat4 TrackballCamera::getViewMatrix() const{
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-_m_fDistance));
        viewMatrix = glm::rotate(viewMatrix, glm::radians(_m_fAngleX), glm::vec3(1, 0, 0));
        viewMatrix = glm::rotate(viewMatrix, glm::radians(_m_fAngleY), glm::vec3(0, 1, 0));
        return viewMatrix;
    }
}
