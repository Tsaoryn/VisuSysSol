#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sun.hpp>

#include <glimac/SunProgram.hpp>
#include <glimac/PlanetProgram.hpp>
#include <glimac/MoonProgram.hpp>
#include <iostream>

namespace glimac {
    class Selector{
        private:
            SDLWindowManager* _windowManager;
            int _mode = 0;
            Sun* _sun;
			
			void selectAction();
        public:
            Selector(SDLWindowManager* windowManager, char* path) : _windowManager(windowManager){
                 _sun = new Sun(path);
            }
            
            int mainLoop();
    };
}
