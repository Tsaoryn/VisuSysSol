#include "glimac/Planet.hpp"
#include <iostream>

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
    
    void Planet::drawPlanet(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
        return;
        if(_extra && _rings)
            this->drawPlanetRing(sunDiameter, sunRotation, nb_vertex, t, camera);
        else if(_extra)
            this->drawPlanetExtra(sunDiameter, sunRotation, nb_vertex, t, camera);
        else
            this->drawSimplePlanet(sunDiameter, sunRotation, nb_vertex, t, camera);
    }
    
    void Planet::drawPlanetRing(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
		
    }
    
    void Planet::drawPlanetExtra(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
       
    }
    
    void Planet::drawSimplePlanet(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
		float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
    }
    
    void Planet::drawPlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t,GLuint vao, Camera* camera){
		if(_extra && _rings)
            this->drawPlanetRingAlone(sunDiameter,sunRotation,nb_vertex, t, vao, camera);
        else if(_extra)
            this->drawPlanetExtraAlone(sunDiameter,sunRotation,nb_vertex, t, vao, camera);
        else
            this->drawSimplePlanetAlone(sunDiameter,sunRotation,nb_vertex, t, vao, camera);
	}
	
	void Planet::drawPlanetRingAlone(float sunDiameter, float sunRotation, float nb_vertex, float t,GLuint vao, Camera* camera){
       //bind
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindVertexArray(vao);
        
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, vao, camera);
		}
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Planet::drawPlanetExtraAlone(float sunDiameter, float sunRotation, float nb_vertex, float t,GLuint vao, Camera* camera){
       //bind
        _programPlanet.m_Program.use();
        
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glUniform1i(_programPlanet.uExtraTexture, 1);
        glBindVertexArray(vao);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,_textureExtra);
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
                glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, vao, camera);
		}
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Planet::drawSimplePlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t,GLuint vao, Camera* camera){
		
        //bind
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindVertexArray(vao);
        
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, vao, camera);
		}
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
