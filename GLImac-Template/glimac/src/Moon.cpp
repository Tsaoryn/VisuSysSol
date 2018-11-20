#include "glimac/Moon.hpp"

namespace glimac{

    void Moon:initMoon(std::string name){
        list<std::string> lines = {};
        readFileArray("Satellites.txt", &lines);
        std::list<std::array<string,5>> list = splitInArray(lines);

        for(std::array tab : list)
            if(tab[0] == name){
                _ellipse = stof(tab[1])+stof(tab[2]);
                _diameter = stof(tab[3]);
                _inclination = stof(tab[4]);
                break;
            }
    }

    void Moon::initTexture(){
        glGenTextures(1,&_textureMoon);
        glBindTexture(GL_TEXTURE_2D, _textureMoon);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgMoon->getWidth(),_imgMoon->getHeight(),0,GL_RGBA,GL_FLOAT,_imgMoon->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    std::string Moon::getName(){
        return _name;
    }
    
    void Moon::deleteTextures(){
        glDeleteTextures(1,&_textureMoon);
    }
}
