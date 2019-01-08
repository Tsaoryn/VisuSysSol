#include "glimac/Moon.hpp"

namespace glimac{

    void Moon::initTexture(){
        glGenTextures(1,&_textureMoon);
        glBindTexture(GL_TEXTURE_2D, _textureMoon);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgMoon->getWidth(),_imgMoon->getHeight(),0,GL_RGBA,GL_FLOAT,_imgMoon->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Moon::drawMoon(float planetDiameter, float nb_vertex, float t, GLuint vao){
    
    }
    
    std::string Moon::getName(){
        return _name;
    }
    
    void Moon::deleteTextures(){
        glDeleteTextures(1,&_textureMoon);
    }
}
