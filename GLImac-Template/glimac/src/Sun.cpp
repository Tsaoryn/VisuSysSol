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
        std::list<Moon*> moons = {};
        std:string subPath = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template";
        
        std::string pathMoon = subPath+"/assets/textures/MoonMap.jpg";
        Moon moon = {path,"Moon",pathMoon};
        Moon Phobos = {path,"Phobos",pathMoon};
        Moon Demios = {path,"Demios",pathMoon};
        Moon Callisto = {path,"Callisto",pathMoon};
        Moon Ganymede = {path,"Ganymede",pathMoon};
        Moon Europa = {path,"Europa",pathMoon};
        Moon Io = {path,"Io",pathMoon};
        Moon Mimas = {path,"Mimas",pathMoon};
        Moon Enceladus = {path,"Enceladus",pathMoon};
        Moon Tethys = {path,"Tethys",pathMoon};
        Moon Dione = {path,"Dione",pathMoon};
        Moon Rhea = {path,"Rhea",pathMoon};
        Moon Titan = {path,"Titan",pathMoonf};
        Moon Hyperion = {path,"Hyperion",pathMoon};
        Moon Iapetus = {path,"Iapetus",pathMoon};
        Moon Ariel = {path,"Ariel",pathMoon};
        Moon Umbriel = {path,"Umbriel",pathMoon};
        Moon Titania = {path,"Titania",pathMoon};
        Moon Oberon = {path,"Oberon",pathMoon};
        Moon Miranda = {path,"Miranda",pathMoon};
        Moon Triton = {path,"Triton",pathMoon};
        Moon Nereid = {path,"Nereid",pathMoon};
        Moon Charon = {path,"Charon",pathMoon};
                
        Planet Mercury = {path,subPath+"/assets/textures/MercuryMap.jpg", "", moons, false, false,69800000.0f,46000000.0f, 4879.0f, 88.0f, 4222.6f,7.0f};
        Planet Venus = {path,subPath+"/assets/textures/VenusMap.jpg", "", moons, false, false,108900000.0f,107500000.0f, 12104.0f, 224.7f, 2802.0f,3.4f};
        moons.push_back(&moon);
        Planet Earth = {path,subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap.jpg", moons, true, false,152100000.0f,147100000.0f, 12756.0f, 365.2f,24.0f,0.0f};
        moons.clear();
        moons.push_back(&Phobos);
        moons.push_back(&Demios);
        Planet Mars = {path,subPath+"/assets/textures/MarsMap.jpg", "", moons, false, false,249200000.0f,206600000.0f, 6792.0f, 687.0f,24.7f,1.9f };
        moons.clear();
        moons.push_back(&Callisto);
        moons.push_back(&Ganymede);
        moons.push_back(&Europa);
        moons.push_back(&Io);
        Planet Jupiter = {path,subPath+"/assets/textures/JupiterMap.jpg", "", moons, false, false,816600000.0f,740500000.0f, 142984.0f,4331.0f,9.9f,1.3f };
        moons.clear();
        moons.push_back(&Mimas);
        moons.push_back(&Enceladus);
        moons.push_back(&Tethys);
        moons.push_back(&Dione);
        moons.push_back(&Rhea);
        moons.push_back(&Titan);
        moons.push_back(&Hyperion);
        moons.push_back(&Iapetus);
        Planet Saturn = {path,subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolour.jpg", moons, true, true, 1514500000.0f,1352600000.0f, 120536.0f, 10747.0f,10.7f,2.5f };
        moons.clear();
        moons.push_back(&Ariel);
        moons.push_back(&Umbriel);
        moons.push_back(&Titania);
        moons.push_back(&Oberon);
        moons.push_back(&Miranda);
        Planet Uranus = {path,subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolour.jpg", moons, true, true,3003600000.0f,2741300000.0f, 51118.0f, 30589.0f,17.2f, 0.8f };
        moons.clear();
        moons.push_back(&Triton);
        moons.push_back(&Nereid);
        Planet Neptune = {path,subPath+"/assets/textures/NeptuneMap.jpg", "", moons, false, false,4545700000.0f,4444500000.0f, 49528.0f, 59800.0f,16.1f,1.8f };
        moons.clear();
        moons.push_back(&Charon);
        Planet Pluto = {path,subPath+"/assets/textures/PlutoMap.jpg", "", moons, false, false,7375900000.0f,4436800000.0f, 2370.0f, 90560.0f,153.3f,17.2f };
        
        _planets.push_back(&Mercury);
        _planets.push_back(&Venus);
        _planets.push_back(&Earth);
        _planets.push_back(&Mars);
        _planets.push_back(&Jupiter);
        _planets.push_back(&Saturn);
        _planets.push_back(&Uranus);
        _planets.push_back(&Neptune);
        _planets.push_back(&Pluto);
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
