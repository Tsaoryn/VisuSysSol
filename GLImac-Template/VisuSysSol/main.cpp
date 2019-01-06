#include <glimac/Selector.hpp>

using namespace glimac;

int main(int argc, char** argv) {
     /*********************************************************************************
     * WINDOW AND OPENGL INITIALIZATIONS
     *********************************************************************************/
    SDLWindowManager* windowManager = new SDLWindowManager(1000, 1000, "GLImac");
    GLenum glewInitError = glewInit();
    glEnable(GL_DEPTH_TEST);
    
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*****************************************************************************************/
    Selector selector(windowManager,argv[0]);
    return selector.mainLoop();   
}
