#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sun.hpp>

#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <iostream>

namespace glimac {
    /* classe gérant les interractions avec le clavier */
    class Selector{
        private:
            SDLWindowManager* _windowManager;
            TrackballCamera* _camera;
            FreeFlyCamera* _cameraFree;
            bool _freeFlyOn;
            bool _fastModeOn;
            int _mode = 0;
            Sun* _sun;
			
            // selon le mode de vision selectionné, la méthode appropriée est apellée
			void selectAction(float time);
            // retourne un pointeur vers la camera en cours d'utilisation
            Camera* getCamera();
            
        public:
            Selector(SDLWindowManager* windowManager, char* path, bool freeFlyOn = false, bool fastModeOn = false) : _windowManager(windowManager),_freeFlyOn(freeFlyOn),_fastModeOn(fastModeOn){
                 _camera = new TrackballCamera();
                 _cameraFree = new FreeFlyCamera();
                 _sun = new Sun(path);
            }
            // boucle principale gerant toutes les interractions avec l'utilisateur
            int mainLoop();
    };
}
