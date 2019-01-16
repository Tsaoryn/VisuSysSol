#include "glimac/FreeFlyCamera.hpp"

namespace glimac{
    void FreeFlyCamera::computeDirectionVectors(){
        float Cos_t = cos(_m_fTheta);
        float Cos_p = cos(_m_fPhi);
        float Sin_p = sin(_m_fPhi);
        float Sin_t = sin(_m_fTheta);
        
        _m_FrontVector = glm::vec3(Cos_t * Sin_p, Sin_t, Cos_t * Cos_p);
        _m_LeftVector = glm::vec3(sin(_m_fPhi + (M_PI/2.0f)), 0, cos(_m_fPhi + (M_PI/2.0f)));
        _m_UpVector = glm::cross(_m_FrontVector, _m_LeftVector);
    }
    
    void FreeFlyCamera::moveLeft(float t){
        _m_Position += t*10 * _m_LeftVector;
    }
            
    void FreeFlyCamera::moveFront(float t){
        _m_Position += t*10 * _m_FrontVector;
    }
    
    void FreeFlyCamera::rotateLeft(float degrees){
        _m_fPhi += degrees/200.0f;
        this->computeDirectionVectors();
    }
            
    void FreeFlyCamera::rotateUp(float degrees){
        _m_fTheta += degrees/200.0f;
        this->computeDirectionVectors();
    }
    
    glm::mat4 FreeFlyCamera::getViewMatrix() const{
        return glm::lookAt(_m_Position, _m_Position+_m_FrontVector, _m_UpVector);
    }
}
