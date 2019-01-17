#pragma once

using namespace std;

namespace glimac {
	/* classe abstraite regroupant la TrackBall Camera et la Free Fly Camera */
    class Camera{
        public:
            virtual void moveFront(float delta) = 0;
            virtual void rotateLeft(float degrees) = 0;
            virtual void rotateUp(float degrees) = 0;
            virtual glm::mat4 getViewMatrix(bool isBackground) const = 0;
    };
}
