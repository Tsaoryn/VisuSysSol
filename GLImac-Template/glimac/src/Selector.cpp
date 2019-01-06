#include "glimac/Selector.hpp"
namespace glimac{
	
	int Selector::mainLoop(){
		bool done = false;
		while(!done) {
			// Event loop:
			SDL_Event e;
			while(_windowManager->pollEvent(e)) {
				if(e.type == SDL_QUIT) {
					done = true; // Leave the loop after this iteration
				}
			}
			/***************************************************************************************
			 *RENDERING CODE
			 ***************************************************************************************/
			/*Events*/ 
			if( e.type == SDL_KEYDOWN ){
				if (_windowManager->isKeyPressed(SDLK_m))
                    _mode = 1;
                else if(_windowManager->isKeyPressed(SDLK_v))
					_mode = 2;
				else if(_windowManager->isKeyPressed(SDLK_e))
					_mode = 3;
				else if(_windowManager->isKeyPressed(SDLK_r))
					_mode = 4;
				else if(_windowManager->isKeyPressed(SDLK_j))
					_mode = 5;
				else if(_windowManager->isKeyPressed(SDLK_s))
					_mode = 6;
				else if(_windowManager->isKeyPressed(SDLK_u))
					_mode = 7;
				else if(_windowManager->isKeyPressed(SDLK_n))
					_mode = 8;
				else if(_windowManager->isKeyPressed(SDLK_p))
					_mode = 9;
				else if(_windowManager->isKeyPressed(SDLK_q))
					_mode = 0;
				else if(_windowManager->isKeyPressed(SDLK_w))
					_mode = 11;
				else if(_windowManager->isKeyPressed(SDLK_x))
					_mode = 12;
			}
			/***************************************************************************************/ 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->selectAction();
			_windowManager->swapBuffers();
		}
		_sun->deleteTextures();
		return EXIT_SUCCESS;
	}
	
	void Selector::selectAction(){
		if(_mode<0 || _mode>12)
			return;
		switch(_mode) {
			case 0:
				_sun->drawSystem(_windowManager->getTime());
				break;
			case 11:
				_sun->drawSystem(_windowManager->getTime());
				break;
			case 12:
				_sun->drawSystem(_windowManager->getTime());
				break;
			default:
				_sun->drawOnePlanet(_mode-1,_windowManager->getTime());
				break;
		}
	}
}
