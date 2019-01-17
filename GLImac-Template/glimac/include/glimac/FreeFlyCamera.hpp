#pragma once
#include "glimac/glm.hpp"
#include <glimac/Camera.hpp>
#include <math.h>

namespace glimac {
    /* Classe qui implémente la classe Camera, et qui représente la Free Fly Camera */
    class FreeFlyCamera : public Camera{
        private:
            glm::vec3 _m_Position;
            float _m_fPhi;
            float _m_fTheta;
            glm::vec3 _m_FrontVector;
            glm::vec3 _m_LeftVector;
            glm::vec3 _m_UpVector;

            //calcul les vecteurs de déplacement de la camera
            void computeDirectionVectors();

        public:
            FreeFlyCamera(glm::vec3 m_Position = glm::vec3(0,0,0), float m_fPhi = M_PI, float m_fTheta = 0.0f): _m_Position(m_Position), _m_fPhi(m_fPhi), _m_fTheta(m_fTheta){
                this->computeDirectionVectors();
            }
            // deplace la camera sur l'axe horizontal
            void moveLeft(float t);
            // deplace la camera sur l'axe Z
            void moveFront(float t);
            // tourne la camera sur l'axe horizontal
            void rotateLeft(float degrees);
            // tourne la camera sur l'axe vertical
            void rotateUp(float degrees);
            // retourne la viewMatrix de la camera
            glm::mat4 getViewMatrix() const;
    };
}
