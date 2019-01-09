#include "glimac/Selector.hpp"
namespace glimac{
	
	int Selector::mainLoop(){
		bool done = false;
        glm::vec2 mousePosition = _windowManager->getMousePosition();
        glm::vec2 mousePositionDiff; 
        glm::vec2 tmp; 
        
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
            if(_windowManager->isMouseButtonPressed(SDL_BUTTON_RIGHT)){
                tmp = _windowManager->getMousePosition();
                mousePositionDiff.x = mousePosition.x - tmp.x;
                mousePositionDiff.y = mousePosition.y - tmp.y;
                mousePosition = tmp;
                _camera->rotateLeft(-mousePositionDiff.x);
                _camera->rotateUp(-mousePositionDiff.y);
            }
            else{
                mousePosition = _windowManager->getMousePosition();
                _camera->rotateLeft(0);
                _camera->rotateUp(0);
            }
            if( e.type == SDL_KEYDOWN ){
                if(_windowManager->isKeyPressed(SDLK_UP))
                    _camera->moveFront(0.1f);
                else if(_windowManager->isKeyPressed(SDLK_DOWN))
                    _camera->moveFront(-0.1f);
				else if (_windowManager->isKeyPressed(SDLK_m))
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
				_sun->drawSystem(_windowManager->getTime(), _camera);
				break;
			case 11:
				_sun->drawSystem(_windowManager->getTime(), _camera);
				break;
			case 12:
				_sun->drawSystem(_windowManager->getTime(), _camera);
				break;
			default:
				_sun->drawOnePlanet(_mode-1,_windowManager->getTime(), _camera);
				break;
		}
	}
}
