#include "glimac/Planet.hpp"

namespace glimac{

    void Planet::initTexture(){
        glGenTextures(1,&_texturePlanet);
        glBindTexture(GL_TEXTURE_2D, _texturePlanet);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgPlanet->getWidth(),_imgPlanet->getHeight(),0,GL_RGBA,GL_FLOAT,_imgPlanet->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Planet::initTextureExtra(){
        glGenTextures(1,&_textureExtra);
        glBindTexture(GL_TEXTURE_2D, _textureExtra);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgExtra->getWidth(),_imgExtra->getHeight(),0,GL_RGBA,GL_FLOAT,_imgExtra->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Planet::drawPlanet(float sunDiameter, float sunRotation, float nb_vertex, float t){
        printf("%f\n",_orbitalInclination);
        printf("%f\n",_lengthDays);
        printf("%f\n",_orbitalPeriod);
        printf("%f\n",_perihelion);
        printf("%f\n\n",_aphelion);
        return;
        if(_extra && _rings)
            this->drawPlanetRing(sunDiameter, sunRotation, nb_vertex, t);
        else if(_extra)
            this->drawPlanetExtra(sunDiameter, sunRotation, nb_vertex, t);
        else
            this->drawSimplePlanet(sunDiameter, sunRotation, nb_vertex, t);
    }
    
    void Planet::drawPlanetRing(float sunDiameter, float sunRotation, float nb_vertex, float t){
        _programPlanet.m_Program.use();
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        
        float diffOrbitalPeriod = sunRotation/_orbitalPeriod;
        float diffLengthDays = sunRotation/_lengthDays;
        float diffDiameter = _diameter/sunDiameter;
        float T = t/diffOrbitalPeriod;
        
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)); // Translation global
        MVMatrix = glm::rotate(MVMatrix, T, glm::vec3(0, 1, 0));//rotation autour du soleil
        MVMatrix = glm::rotate(MVMatrix, _orbitalInclination, glm::vec3(1, 0, 0));//inclinaison elliptique
        MVMatrix = glm::translate(MVMatrix, glm::vec3(1.3,0,1.1)); // Translation * Rotation * Translation
        MVMatrix = glm::scale(MVMatrix, glm::vec3(diffDiameter, diffDiameter, diffDiameter)); // Translation * Rotation * Translation * Scale
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, nb_vertex);
        glBindVertexArray(0);
    }
    
    void Planet::drawPlanetExtra(float sunDiameter, float sunRotation, float nb_vertex, float t){
       
    }
    
    void Planet::drawSimplePlanet(float sunDiameter, float sunRotation, float nb_vertex, float t){
       
    }
    
    void Planet::deleteTextures(){
        glDeleteTextures(1,&_texturePlanet);
        if(_extra)
            glDeleteTextures(1,&_textureExtra);
        
        for(auto moon : _moons){
            moon->deleteTextures();
        }
    }
}
