#include "glimac/Sun.hpp"

namespace glimac{

    void Sun::initTexture(){
        glGenTextures(1,&_textureSun);
        glBindTexture(GL_TEXTURE_2D, _textureSun);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgSun->getWidth(),_imgSun->getHeight(),0,GL_RGBA,GL_FLOAT,_imgSun->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Sun::initVboVao(){
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
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
    void Sun::initPlanets(char* path){
        //don't forget to change subPath when you change your installation
        std:string subPath = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template";
        /*
        Moon moon = {path,"Moon"};
        Moon Phobos = {path,"Phobos"};
        Moon Demios = {path,"Demios"};
        Moon Callisto = {path,"Callisto"};
        Moon Ganymede = {path,"Ganymede"};
        Moon Europa = {path,"Europa"};
        Moon Io = {path,"Io"};
        Moon Mimas = {path,"Mimas"};
        Moon Enceladus = {path,"Enceladus"};
        Moon Tethys = {path,"Tethys"};
        Moon Dione = {path,"Dione"};
        Moon Rhea = {path,"Rhea"};
        Moon Titan = {path,"Titan"};
        Moon Hyperion = {path,"Hyperion"};
        Moon Iapetus = {path,"Iapetus"};
        Moon Ariel = {path,"Ariel"};
        Moon Umbriel = {path,"Umbriel"};
        Moon Titania = {path,"Titania"};
        Moon Oberon = {path,"Oberon"};
        Moon Miranda = {path,"Miranda"};
        Moon Triton = {path,"Triton"};
        Moon Nereid = {path,"Nereid"};
        Moon Charon = {path,"Charon"};*/

        Planet Mercury = {"Mercury", path, subPath+"/assets/textures/MercuryMap.jpg", ""};
        Planet Venus = {"Venus", path, subPath+"/assets/textures/VenusMap.jpg", ""};
        Planet Earth = {"Earth", path,subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap.jpg"};
        Planet Mars = {"Mars", path,subPath+"/assets/textures/MarsMap.jpg", ""};
        Planet Jupiter = {"Jupiter", path,subPath+"/assets/textures/JupiterMap.jpg", ""};
        Planet Saturn = {"Saturn", path,subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolour.jpg"};
        Planet Uranus = {"Uranus", path,subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolour.jpg"};
        Planet Neptune = {"Neptune", path,subPath+"/assets/textures/NeptuneMap.jpg", ""};
        Planet Pluto = {"Pluto", path,subPath+"/assets/textures/PlutoMap.jpg", ""};

        /*
        _planets.push_back(&Mercury);
        _planets.push_back(&Venus);
        _planets.push_back(&Earth);
        _planets.push_back(&Mars);
        _planets.push_back(&Jupiter);
        _planets.push_back(&Saturn);
        _planets.push_back(&Uranus);
        _planets.push_back(&Neptune);
        _planets.push_back(&Pluto);*/
    }

    void Sun::drawSystem(float t){
        //bind
        _programSun.m_Program.use();
        glBindTexture(GL_TEXTURE_2D,_textureSun);
        glUniform1i(_programSun.uTexture, 0);
        glBindVertexArray(_vao);
        /*to do camera*/
        glm::mat4 viewMatrix = glm::mat4(1.0f);
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f)* viewMatrix;
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t/1.0f, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programSun.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programSun.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programSun.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*_sphere.getVertexCount());
        glBindVertexArray(0);
        
        int num = 1;
        for (Planet * planet : _planets) {
            planet->drawPlanet(_diameter,_rotation, _sphere.getVertexCount(),1.0f);
            num++;
        }
        
    }
    
    void Sun::deleteTextures(){
        glDeleteTextures(1,&_textureSun);
        for(Planet * planet : _planets){
            planet->deleteTextures();
        }
    }
}
