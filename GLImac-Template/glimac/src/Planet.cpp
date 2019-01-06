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
        return;
        if(_extra && _rings)
            this->drawPlanetRing(sunDiameter, sunRotation, nb_vertex, t);
        else if(_extra)
            this->drawPlanetExtra(sunDiameter, sunRotation, nb_vertex, t);
        else
            this->drawSimplePlanet(sunDiameter, sunRotation, nb_vertex, t);
    }
    
    void Planet::drawPlanetRing(float sunDiameter, float sunRotation, float nb_vertex, float t){

    }
    
    void Planet::drawPlanetExtra(float sunDiameter, float sunRotation, float nb_vertex, float t){
       
    }
    
    void Planet::drawSimplePlanet(float sunDiameter, float sunRotation, float nb_vertex, float t){
       
    }
    
    void Planet::drawPlanetAlone(float nb_vertex, float t,GLuint vao ){
		if(_extra && _rings)
            this->drawPlanetRingAlone(nb_vertex, t, vao);
        else if(_extra)
            this->drawPlanetExtraAlone(nb_vertex, t, vao);
        else
            this->drawSimplePlanetAlone(nb_vertex, t, vao);
	}
	
	void Planet::drawPlanetRingAlone(float nb_vertex, float t,GLuint vao){
       
    }
    
    void Planet::drawPlanetExtraAlone(float nb_vertex, float t,GLuint vao){
       //bind
        _programPlanet.m_Program.use();
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glBindTexture(GL_TEXTURE_2D,_textureExtra);
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glUniform1i(_programPlanet.uExtraTexture, 0);
        glBindVertexArray(vao);
        /*to do camera*/
        glm::mat4 viewMatrix = glm::mat4(1.0f);
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f)* viewMatrix;
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t/1.0f, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        
        /*for(auto moon : _moons){
			moon->drawMoon();
		}*/
            
        glBindVertexArray(0);
    }
    
    void Planet::drawSimplePlanetAlone(float nb_vertex, float t,GLuint vao){
        //bind
        _programPlanet.m_Program.use();
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindVertexArray(vao);
        /*to do camera*/
        glm::mat4 viewMatrix = glm::mat4(1.0f);
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f)* viewMatrix;
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t/1.0f, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        glBindVertexArray(0);
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
