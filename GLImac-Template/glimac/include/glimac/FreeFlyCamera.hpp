#pragma once
#include "glimac/glm.hpp"
#include <math.h>

namespace glimac {
    class FreeFlyCamera{
        private:
            glm::vec3 _m_Position;
            float _m_fPhi;
            float _m_fTheta;
            glm::vec3 _m_FrontVector;
            glm::vec3 _m_LeftVector;
            glm::vec3 _m_UpVector;
            void computeDirectionVectors();
        public:
            FreeFlyCamera(glm::vec3 m_Position = glm::vec3(0,0,0), float m_fPhi = M_PI, float m_fTheta = 0.0f): _m_Position(m_Position), _m_fPhi(m_fPhi), _m_fTheta(m_fTheta){
                this->computeDirectionVectors();
            }
            void moveLeft(float t);
            void moveFront(float t);
            void rotateLeft(float degrees);
            void rotateUp(float degrees);
            glm::mat4 getViewMatrix() const;
    };
}
