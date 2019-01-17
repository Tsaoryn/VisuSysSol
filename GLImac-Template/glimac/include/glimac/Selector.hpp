#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sun.hpp>

#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <iostream>
#include <memory>

namespace glimac {
    /* classe gérant les interractions avec le clavier */
    class Selector{
        private:
            SDLWindowManager* _windowManager;
            std::shared_ptr<TrackballCamera> _camera;
            std::shared_ptr<FreeFlyCamera> _cameraFree;
            SphereDrawer _background;
            bool _freeFlyOn;
            bool _fastModeOn;
            int _mode = 0;
            std::shared_ptr<Sun> _sun;
			
            // selon le mode de vision selectionné, la méthode appropriée est apellée
			void selectAction(float time);
            // retourne un pointeur vers la camera en cours d'utilisation
            std::shared_ptr<Camera> getCamera();
            
        public:
            Selector(SDLWindowManager* windowManager, char* path, bool freeFlyOn = false, bool fastModeOn = false) : _windowManager(windowManager),_freeFlyOn(freeFlyOn),_fastModeOn(fastModeOn){
                ifstream file("../GLImac-Template/assets/ressources/path.txt");
                std::string subPath;
                getline(file, subPath);
                std::string pathBackground = subPath+"/assets/textures/Stars.jpg";
                
                _camera = std::make_shared<TrackballCamera>();
                _cameraFree = std::make_shared<FreeFlyCamera>();
                _background = SphereDrawer(path, pathBackground, "", 100.0f, false, false, true);
                _sun = shared_ptr<Sun>(new Sun(path, subPath));
            }
            // boucle principale gerant toutes les interractions avec l'utilisateur
            int mainLoop();
    };
}
