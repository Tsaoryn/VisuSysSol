#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/Ellipse.hpp"
#include "glimac/common.hpp"

namespace glimac {
    
    void Ellipse::initVertices(){
		float a = log10((_aphelion+_perihelion)/2.0f)+_additionalNum;
		float b = log10(((_aphelion+_perihelion)/2.0f)*std::sqrt(1-(_eccentricity*_eccentricity)))+_additionalNum;
		float radian;
		
        for(float degree=0; degree<360; degree=degree+0.04f){
			radian = glm::radians(degree);
			float x = a*cos(radian);
            float y = b*sin(radian);
            
			ShapeVertex vertex;
			         
            vertex.texCoords.x = x;
            vertex.texCoords.y = y;

            vertex.normal.x = x;
            vertex.normal.y = y;
            vertex.normal.z = 0;
            
            vertex.position = glm::vec3(x,y,0);
            
            m_Vertices.push_back(vertex);
        }
        m_nVertexCount = m_Vertices.size();
    }
    
    std::pair<float,float> Ellipse::getEllipseAandB(){
		float a = log10((_aphelion+_perihelion)/2.0f)+_additionalNum;
		float b = log10(((_aphelion+_perihelion)/2.0f)*std::sqrt(1-(_eccentricity*_eccentricity)))+_additionalNum;
		return std::pair<float,float>(a,b);
	}
    
    void Ellipse::initVboVao(){
		const int nb_floats = 8*m_nVertexCount;
		const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_POSITION_SHADER = 0;
        const GLuint VERTEX_ATTR_NORMAL_SHADER = 1;
        
        /*vbo*/
        glGenBuffers(1, &_vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            const ShapeVertex * vertices = &m_Vertices[0];
            glBufferData(GL_ARRAY_BUFFER, nb_floats*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        /*vao*/
        glGenVertexArrays(1, &_vao);
        
        glBindVertexArray(_vao);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION_SHADER);
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL_SHADER);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                glVertexAttribPointer(VERTEX_ATTR_POSITION_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) 0);
                glVertexAttribPointer(VERTEX_ATTR_NORMAL_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) (3*sizeof(GLfloat)));
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
    
    void Ellipse::draw(Camera* camera){
        _programEllipse.m_Program.use();
        glBindVertexArray(_vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
        MVMatrix = glm::rotate(MVMatrix, _inclination, glm::vec3(1, 0, 0));
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programEllipse.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programEllipse.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programEllipse.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_LINE_LOOP, 0, m_nVertexCount);
        
        glBindVertexArray(0);
    }


}
