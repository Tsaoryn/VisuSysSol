#include "glimac/Moon.hpp"
#include <math.h>
#include <iostream>

namespace glimac{

    void Moon::initTexture(){
        glGenTextures(1,&_textureMoon);
        glBindTexture(GL_TEXTURE_2D, _textureMoon);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgMoon->getWidth(),_imgMoon->getHeight(),0,GL_RGBA,GL_FLOAT,_imgMoon->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    
    void Moon::drawMoon(float planetDiameter, glm::mat4 ProjMatrix, float nb_vertex, float t, GLuint vao, Camera* camera){
		float scaleValue = std::pow(10,_diameter)/std::pow(10,planetDiameter);
		_ellipse.draw(camera);
        
        float radian = glm::radians(t*15);
        
        std::pair<float,float> tuple = _ellipse.getEllipseAandB();
		float xFinal = tuple.first*cos(radian);
        float Y = tuple.second*sin(radian);
        float y = Y*cos(glm::radians(90.0f));
        float z = Y*sin(glm::radians(90.0f));
        
        float yFinal = y*cos(_inclination)-sin(_inclination)*z;
        float zFinal = y*sin(_inclination)+cos(_inclination)*z;
                
        _programMoon.m_Program.use();
        glUniform1i(_programMoon.uMoonTexture, 0);
        glBindTexture(GL_TEXTURE_2D,_textureMoon);
        glBindVertexArray(vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix; // Translation
        MVMatrix = glm::translate(MVMatrix,glm::vec3(xFinal,yFinal,zFinal));
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); // Translation * Rotation * Translation * Scale
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programMoon.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programMoon.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programMoon.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);

        glBindTexture(GL_TEXTURE_2D,0);
    }
    
    std::string Moon::getName(){
        return _name;
    }
    
    void Moon::deleteTextures(){
        glDeleteTextures(1,&_textureMoon);
    }
}
