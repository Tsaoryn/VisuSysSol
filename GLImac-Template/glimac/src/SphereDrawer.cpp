#include "glimac/SphereDrawer.hpp"
#include <iostream>

namespace glimac{

    void SphereDrawer::initTexture(){
        glGenTextures(1,&_textureOne);
        glBindTexture(GL_TEXTURE_2D, _textureOne);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgOne->getWidth(),_imgOne->getHeight(),0,GL_RGBA,GL_FLOAT,_imgOne->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void SphereDrawer::initTextureExtra(){
        glGenTextures(1,&_textureTwo);
        glBindTexture(GL_TEXTURE_2D, _textureTwo);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgTwo->getWidth(),_imgTwo->getHeight(),0,GL_RGBA,GL_FLOAT,_imgTwo->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void SphereDrawer::initVboVao(){
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
    
    void SphereDrawer::drawPlanet(float t, Camera* camera, bool toTranslate, bool _extra, float _lengthDays, float scaleValue, glm::vec3 vec){   
        _program.m_Program.use();
        glUniform1i(_program.uTexture, 0);
        if(_extra){
            glUniform1i(_program.uExtraTexture, 1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,_textureOne);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,_textureTwo);
        }
        else{
            glBindTexture(GL_TEXTURE_2D,_textureOne);
        }
        
        glBindVertexArray(_vao);
        
        //Matrices------------------------------------------------------------------------------------------------------------------------
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = viewMatrix;
        if(!toTranslate)
            MVMatrix = glm::rotate(MVMatrix, (t/_lengthDays), glm::vec3(0, 1, 0));
        if(toTranslate)
            MVMatrix = glm::translate(MVMatrix,vec);
        
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_program.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_program.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_program.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*_sphere.getVertexCount());

        if(_extra)
            glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,0);
    }
    
    int SphereDrawer::getNbVertices(){
        return _sphere.getVertexCount();
    }
    
    void SphereDrawer::deleteTextures(bool extra){
        glDeleteTextures(1,&_textureOne);
        if(extra)
            glDeleteTextures(1,&_textureTwo);
    }
}
