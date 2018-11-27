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
        //std:string subPath = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template";
        std:string subPath = "/home/2ins2/nhipolit/Documents/3D/VisuSysSol/GLImac-Template";

        
        Moon moon = {path,"Moon", 384400.+0.0549, 3475., 5.145};
        Moon Phobos = {path,"Phobos", 9378.+0.0151, 22.5, 1.08};
        Moon Demios = {path,"Demios", 23459.+0.0005, 12., 1.79};
        Moon Callisto = {path,"Callisto", 1882710.+0.007, 4821., 0.19};
        Moon Ganymede = {path,"Ganymede", 671030.+0.009, 3122., 0.47};
        Moon Europa = {path,"Europa", 671030.+0.009, 3122., 0.47};
        Moon Io = {path,"Io", 421700.+0.004, 3643., 0.04};
        Moon Mimas = {path,"Mimas", 185520.+0.0202, 392., 1.53};
        Moon Enceladus = {path,"Enceladus", 238020.+0.0045, 498., 0.};
        Moon Tethys = {path,"Tethys", 294660., 1060., 1.86};
        Moon Dione = {path,"Dione", 377400.+0.0022, 1120., 0.02};
        Moon Rhea = {path,"Rhea", 527040.+0.0010, 1530., 0.35};
        Moon Titan = {path,"Titan", 1221830.+0.0292, 5150., 0.33};
        Moon Hyperion = {path,"Hyperion", 1481100.0+0.1042, 286., 0.43};
        Moon Iapetus = {path,"Iapetus", 3561300.+0.0283, 1460., 14.72};
        Moon Ariel = {path,"Ariel", 199900.+0.0012, 1158., 0.04};
        Moon Umbriel = {path,"Umbriel", 266000.+0.0039, 1169., 0.13};
        Moon Titania = {path,"Titania", 436300.+0.0011, 1577., 0.08};
        Moon Oberon = {path,"Oberon", 583500.+0.0014, 1523., 0.07};
        Moon Miranda = {path,"Miranda", 129900.+0.0013, 472.0, 4.34};
        Moon Triton = {path,"Triton", 354760.+0.000016, 2707., 157.345};
        Moon Nereid = {path,"Nereid", 5513400.+0.7512, 340., 7.23};
        Moon Charon = {path,"Charon", 19591., 1212., 0.00005};

        Planet Mercury = {"Mercury", path, subPath+"/assets/textures/MercuryMap.jpg", "", false, false, 69800000., 46000000., 4879., 88., 4222.6, 7.};
        Planet Venus = {"Venus", path, subPath+"/assets/textures/VenusMap.jpg", "", false, false, 108900000., 107500000., 12104., 224.7, 2802., 3.4};
        Planet Earth = {"Earth", path,subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap.jpg", true, false, 152100000., 147100000., 12756., 365.2, 24., 0};
        Planet Mars = {"Mars", path,subPath+"/assets/textures/MarsMap.jpg", "", false, false, 249200000., 206600000., 6792., 687., 24.7, 1.9};
        Planet Jupiter = {"Jupiter", path,subPath+"/assets/textures/JupiterMap.jpg", "", false, false, 816600000., 740500000., 142984., 4331., 9.9, 1.3};
        Planet Saturn = {"Saturn", path,subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolour.jpg", true, true, 1514500000., 1352600000., 120536., 10747., 10.7, 2.5};
        Planet Uranus = {"Uranus", path,subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolour.jpg", true, true, 3003600000., 2741300000., 51118., 30589., 17.2, 0.8};
        Planet Neptune = {"Neptune", path,subPath+"/assets/textures/NeptuneMap.jpg", "", false, false, 4545700000., 4444500000., 49528., 59800., 16.1, 1.8};
        Planet Pluto = {"Pluto", path,subPath+"/assets/textures/PlutoMap.jpg", "", false, false, 7375900000., 4436800000., 2370., 90560., 153.3, 17.2};

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
