#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sun.hpp>

#include <glimac/SunProgram.hpp>
#include <glimac/PlanetProgram.hpp>
#include <glimac/MoonProgram.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <iostream>

namespace glimac {
    class Selector{
        private:
            SDLWindowManager* _windowManager;
            TrackballCamera* _camera;
            FreeFlyCamera* _cameraFree;
            bool _freeFlyOn;
            int _mode = 0;
            Sun* _sun;
			
			void selectAction();
            Camera* getCamera();
            
        public:
            Selector(SDLWindowManager* windowManager, char* path, bool freeFlyOn = false) : _windowManager(windowManager),_freeFlyOn(freeFlyOn){
                 _camera = new TrackballCamera();
                 _cameraFree = new FreeFlyCamera();
                 _sun = new Sun(path);
            }
            
            int mainLoop();
    };
}
