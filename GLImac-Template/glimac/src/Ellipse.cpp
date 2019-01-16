#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/Ellipse.hpp"
#include "glimac/common.hpp"

namespace glimac {
    
    void Ellipse::initVertices(){
		float radian;
		
        for(float degree=0; degree<360; degree=degree+0.04f){
			radian = glm::radians(degree);
			float x = a*cos(radian);
            float z = b*sin(radian);
            
			ShapeVertex vertex;
			         
            vertex.texCoords.x = x;
            vertex.texCoords.y = z;
			
            vertex.normal.x = x;
            vertex.normal.y = -sin(_inclination)*z;
            vertex.normal.z = cos(_inclination)*z;
            
            vertex.position = glm::vec3(x,-sin(_inclination)*z,cos(_inclination)*z);
            
            m_Vertices.push_back(vertex);
        }
        m_nVertexCount = m_Vertices.size();
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
    
    glm::vec3 Ellipse::translationVector(float angle){
        float radian = glm::radians(angle);
        
		float xFinal = a*cos(radian);
        float Y = b*sin(radian);
        float y = Y*cos(glm::radians(90.0f));
        float z = Y*sin(glm::radians(90.0f));
        
        float yFinal = y*cos(_inclination)-sin(_inclination)*z;
        float zFinal = y*sin(_inclination)+cos(_inclination)*z;
        
        
        return glm::vec3(xFinal,yFinal,zFinal);
    }
    
    void Ellipse::draw(Camera* camera){
        _programEllipse.m_Program.use();
        glBindVertexArray(_vao);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = viewMatrix;
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programEllipse.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programEllipse.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programEllipse.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_LINE_LOOP, 0, m_nVertexCount);
        
        glBindVertexArray(0);
    }


}
