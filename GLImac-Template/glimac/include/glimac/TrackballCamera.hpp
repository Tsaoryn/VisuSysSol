#pragma once
#include "glimac/glm.hpp"
#include <glimac/Camera.hpp>

namespace glimac {
    /* classe faite en TP */
    class TrackballCamera : public Camera{
        private:
            float _m_fDistance;
            float _m_fAngleX;
            float _m_fAngleY;
        public:
            TrackballCamera(float m_fDistance=5.0f, float m_fAngleX=0.0f, float m_fAngleY=0.0f): _m_fDistance(m_fDistance), _m_fAngleX(m_fAngleX), _m_fAngleY(m_fAngleY){
            }
            void moveFront(float delta);
            void rotateLeft(float degrees);
            void rotateUp(float degrees);
            glm::mat4 getViewMatrix(bool isBackground) const;
    };
}
