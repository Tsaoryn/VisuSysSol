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
    
    void Planet::initVboVao(){
        const int nb_floats = 8*_sphere.getVertexCount();
        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_POSITION_SHADER = 0;
        const GLuint VERTEX_ATTR_NORMAL_SHADER = 1;
        const GLuint VERTEX_ATTR_TEX_SHADER = 2;
        
        /*vbo*/
        glGenBuffers(1, &_vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            const ShapeVertex * vertices = _sphere.getDataPointer();
            glBufferData(GL_ARRAY_BUFFER, nb_floats*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        /*vao*/
        glGenVertexArrays(1, &_vao);
        
        glBindVertexArray(_vao);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION_SHADER);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL_SHADER);
            glEnableVertexAttribArray(VERTEX_ATTR_TEX_SHADER);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                glVertexAttribPointer(VERTEX_ATTR_POSITION_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) 0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) (3*sizeof(GLfloat)));
                glVertexAttribPointer(VERTEX_ATTR_TEX_SHADER, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) (6*sizeof(GLfloat)));
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//GL_FILL
    }
    
    void Planet::drawPlanet(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera){
        if(_extra && _rings)
            this->drawPlanetRing(sunDiameter, vao, nb_vertex, t, camera);
        else if(_extra)
            this->drawPlanetExtra(sunDiameter, vao, nb_vertex, t, camera);
        else
            this->drawSimplePlanet(sunDiameter, vao, nb_vertex, t, camera);
    }
    
    void Planet::drawPlanetRing(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera){
		float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
		_ellipse.draw(camera);
        
        float radian = glm::radians(t/_orbitalPeriod);
        
        std::pair<float,float> tuple = _ellipse.getEllipseAandB();
		float xFinal = tuple.first*cos(radian);
        float Y = tuple.second*sin(radian);
        float y = Y*cos(glm::radians(90.0f));
        float z = Y*sin(glm::radians(90.0f));
        
        float yFinal = y*cos(_orbitalInclination)-sin(_orbitalInclination)*z;
        float zFinal = y*sin(_orbitalInclination)+cos(_orbitalInclination)*z;
        
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glBindVertexArray(vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix; // Translation
        MVMatrix = glm::rotate(MVMatrix, t/_lengthDays, glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix,glm::vec3(xFinal,yFinal,zFinal));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); // Translation * Rotation * Translation * Scale
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);

        glBindTexture(GL_TEXTURE_2D,0);
    }
    
    void Planet::drawPlanetExtra(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera){
       float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
		_ellipse.draw(camera);
        
        float radian = glm::radians(t/_orbitalPeriod);
        
        std::pair<float,float> tuple = _ellipse.getEllipseAandB();
		float xFinal = tuple.first*cos(radian);
        float Y = tuple.second*sin(radian);
        float y = Y*cos(glm::radians(90.0f));
        float z = Y*sin(glm::radians(90.0f));
        
        float yFinal = y*cos(_orbitalInclination)-sin(_orbitalInclination)*z;
        float zFinal = y*sin(_orbitalInclination)+cos(_orbitalInclination)*z;
        
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glUniform1i(_programPlanet.uExtraTexture, 1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,_textureExtra);
        glBindVertexArray(vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix; // Translation
        MVMatrix = glm::rotate(MVMatrix, t/_lengthDays, glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix,glm::vec3(xFinal,yFinal,zFinal));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); // Translation * Rotation * Translation * Scale
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Planet::drawSimplePlanet(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera){
		float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
		_ellipse.draw(camera);
        
        float radian = glm::radians(t/_orbitalPeriod);
        
        std::pair<float,float> tuple = _ellipse.getEllipseAandB();
		float xFinal = tuple.first*cos(radian);
        float Y = tuple.second*sin(radian);
        float y = Y*cos(glm::radians(90.0f));
        float z = Y*sin(glm::radians(90.0f));
        
        float yFinal = y*cos(_orbitalInclination)-sin(_orbitalInclination)*z;
        float zFinal = y*sin(_orbitalInclination)+cos(_orbitalInclination)*z;
        
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glBindVertexArray(vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix; // Translation
        MVMatrix = glm::rotate(MVMatrix, t/_lengthDays, glm::vec3(0, 1, 0));
        MVMatrix = glm::translate(MVMatrix,glm::vec3(xFinal,yFinal,zFinal));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); // Translation * Rotation * Translation * Scale
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);

        glBindTexture(GL_TEXTURE_2D,0);
    }
    
    void Planet::drawPlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
		if(_extra && _rings)
            this->drawPlanetRingAlone(sunDiameter,sunRotation,nb_vertex, t, camera);
        else if(_extra)
            this->drawPlanetExtraAlone(sunDiameter,sunRotation,nb_vertex, t, camera);
        else
            this->drawSimplePlanetAlone(sunDiameter,sunRotation,nb_vertex, t, camera);
	}
	
	void Planet::drawPlanetRingAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
       //bind
       //float scaleValue = std::pow(10,_diameter)/std::pow(10,_diameter*2);
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindVertexArray(_vao);
        
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t*10/_lengthDays, glm::vec3(0, -1, 0));
        //MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); 
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, _vao, camera);
		}
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Planet::drawPlanetExtraAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
		//float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
       //bind
        _programPlanet.m_Program.use();
        
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glUniform1i(_programPlanet.uExtraTexture, 1);
        glBindVertexArray(_vao);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,_textureExtra);
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t*10/_lengthDays, glm::vec3(0, -1, 0));
        //MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); 
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, _vao, camera);
		}
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Planet::drawSimplePlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera){
		//float scaleValue = std::pow(10,_diameter)/std::pow(10,sunDiameter);
        //bind
        _programPlanet.m_Program.use();
        glUniform1i(_programPlanet.uPlanetTexture, 0);
        glBindVertexArray(_vao);
        
        glBindTexture(GL_TEXTURE_2D,_texturePlanet);
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t*10/_lengthDays, glm::vec3(0, -1, 0));
        //MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); 
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programPlanet.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programPlanet.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programPlanet.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);
        
        for(auto moon : _moons){
            moon->drawMoon(_diameter, ProjMatrix, nb_vertex, t, _vao, camera);
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
