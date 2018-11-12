#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sun.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <iostream>

using namespace glimac;

int main(int argc, char** argv) {
     /*********************************************************************************
     * WINDOW AND OPENGL INITIALIZATIONS
     *********************************************************************************/
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1000, 1000, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    FilePath applicationPath(argv[0]);
    
    SunProgram sunProgram(applicationPath);
    PlanetProgram planetProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);
    
    
    glEnable(GL_DEPTH_TEST);
    
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*****************************************************************************************/
    Sun sun = {sunProgram, planetProgram, moonProgram};
    
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        /***************************************************************************************
         *RENDERING CODE
         ***************************************************************************************/
        /*Events*/ 
         
        /***************************************************************************************/ 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //sun.drawSystem();
        // Update the display
        windowManager.swapBuffers();
    }
    
    //sun.deleteTextures();
    return EXIT_SUCCESS;
}
