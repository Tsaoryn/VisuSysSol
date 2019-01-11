#pragma once

using namespace std;

namespace glimac {
    class Camera{
        public:
            virtual void moveFront(float delta) = 0;
            virtual void rotateLeft(float degrees) = 0;
            virtual void rotateUp(float degrees) = 0;
            virtual glm::mat4 getViewMatrix() const = 0;
    };
}
