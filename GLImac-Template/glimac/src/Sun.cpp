#include "glimac/Sun.hpp"
#include <iostream>
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
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//GL_FILL
    }
    
    void Sun::initPlanets(char* path){
        //don't forget to change the path in path.txt when you change your location
        std::list<Moon*> moons = {};
        
        ifstream file("../GLImac-Template/assets/ressources/path.txt");
        std::string subPath;
        getline(file, subPath);
 
        
        std::string pathMoon = subPath+"/assets/textures/MoonMap.jpg";
        Moon* moon = new Moon(path,"Moon",pathMoon,384400.0f,0.0549f,3475.0f,5.145f);
        Moon* Phobos = new Moon(path,"Phobos",pathMoon,9378.0f,0.0151f,22.5f,1.08f);
        Moon* Demios = new Moon(path,"Demios",pathMoon,23459.0f,0.0005f,12.0f,1.79f);
        Moon* Callisto = new Moon(path,"Callisto",pathMoon,1882710.0f,0.007f,4821.0f,0.19f);
        Moon* Ganymede = new Moon(path,"Ganymede",pathMoon,1070410.0f,0.001f,5262.0f,0.18f);
        Moon* Europa = new Moon(path,"Europa",pathMoon,671030.0f,0.009f,3122.0f,0.47f);
        Moon* Io = new Moon(path,"Io",pathMoon,421700.0f,0.004f,3643.0f,0.04f);
        Moon* Mimas = new Moon(path,"Mimas",pathMoon,185520.0f,0.0202f,392.0f,1.53f);
        Moon* Enceladus = new Moon(path,"Enceladus",pathMoon,238020.f,0.0045f,498.0f,0.0f);
        Moon* Tethys = new Moon(path,"Tethys",pathMoon,294660.0f,0.0f,1060.0f,1.86f);
        Moon* Dione = new Moon(path,"Dione",pathMoon,377400.0f,0.0022f,1120.0f,0.02f);
        Moon* Rhea = new Moon(path,"Rhea",pathMoon,527040.0f,0.0010f,1530.0f,0.35f);
        Moon* Titan = new Moon(path,"Titan",pathMoon,1221830.0f,0.0292f,5150.0f,0.33f);
        Moon* Hyperion = new Moon(path,"Hyperion",pathMoon,1481100.0f,0.1042f,286.0f,0.43f);
        Moon* Iapetus = new Moon(path,"Iapetus",pathMoon,3561300.0f,0.0283f,1460.0f,14.72f);
        Moon* Ariel = new Moon(path,"Ariel",pathMoon,199900.0f,0.0012f,1158.0f,0.04f);
        Moon* Umbriel = new Moon(path,"Umbriel",pathMoon,266000.0f,0.0039f,1169.0f,0.13f);
        Moon* Titania = new Moon(path,"Titania",pathMoon,436300.0f,0.0011f,1577.0f,0.08);
        Moon* Oberon = new Moon(path,"Oberon",pathMoon,583500.0f,0.0014,1523.0f,0.07f);
        Moon* Miranda = new Moon(path,"Miranda",pathMoon,129900.0f,0.0013,472.0f,4.34f);
        Moon* Triton = new Moon(path,"Triton",pathMoon,354760.0f,0.000016f,2707.0f,157.345f);
        Moon* Nereid = new Moon(path,"Nereid",pathMoon,5513400.0f,0.7512,340.0f,7.23f);
        Moon* Charon = new Moon(path,"Charon",pathMoon,19591.0f,0.0f,1212.0f,0.00005f);
                
        Planet* Mercury = new Planet(path,subPath+"/assets/textures/MercuryMap.jpg", "", moons, false, false,69800000.0f,46000000.0f, 4879.0f, 88.0f, 4222.6f,7.0f);
        Planet* Venus = new Planet(path,subPath+"/assets/textures/VenusMap.jpg", "", moons, false, false,108900000.0f,107500000.0f, 12104.0f, 224.7f, 2802.0f,3.4f);
        moons.push_back(moon);
        Planet* Earth = new Planet(path,subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap.jpg", moons, true, false,152100000.0f,147100000.0f, 12756.0f, 365.2f,24.0f,0.0f);
        moons.clear();
        moons.push_back(Phobos);
        moons.push_back(Demios);
        Planet* Mars = new Planet(path,subPath+"/assets/textures/MarsMap.jpg", "", moons, false, false,249200000.0f,206600000.0f, 6792.0f, 687.0f,24.7f,1.9f) ;
        moons.clear();
        moons.push_back(Callisto);
        moons.push_back(Ganymede);
        moons.push_back(Europa);
        moons.push_back(Io);
        Planet* Jupiter = new Planet(path,subPath+"/assets/textures/JupiterMap.jpg", "", moons, false, false,816600000.0f,740500000.0f, 142984.0f,4331.0f,9.9f,1.3f) ;
        moons.clear();
        moons.push_back(Mimas);
        moons.push_back(Enceladus);
        moons.push_back(Tethys);
        moons.push_back(Dione);
        moons.push_back(Rhea);
        moons.push_back(Titan);
        moons.push_back(Hyperion);
        moons.push_back(Iapetus);
        Planet* Saturn = new Planet(path,subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolour.jpg", moons, true, true, 1514500000.0f,1352600000.0f, 120536.0f, 10747.0f,10.7f,2.5f) ;
        moons.clear();
        moons.push_back(Ariel);
        moons.push_back(Umbriel);
        moons.push_back(Titania);
        moons.push_back(Oberon);
        moons.push_back(Miranda);
        Planet* Uranus = new Planet(path,subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolour.jpg", moons, true, true,3003600000.0f,2741300000.0f, 51118.0f, 30589.0f,17.2f, 0.8f) ;
        moons.clear();
        moons.push_back(Triton);
        moons.push_back(Nereid);
        Planet* Neptune = new Planet(path,subPath+"/assets/textures/NeptuneMap.jpg", "", moons, false, false,4545700000.0f,4444500000.0f, 49528.0f, 59800.0f,16.1f,1.8f) ;
        moons.clear();
        moons.push_back(Charon);
        Planet* Pluto = new Planet(path,subPath+"/assets/textures/PlutoMap.jpg", "", moons, false, false,7375900000.0f,4436800000.0f, 2370.0f, 90560.0f,153.3f,17.2f);
        
        _planets.push_back(Mercury);
        _planets.push_back(Venus);
        _planets.push_back(Earth);
        _planets.push_back(Mars);
        _planets.push_back(Jupiter);
        _planets.push_back(Saturn);
        _planets.push_back(Uranus);
        _planets.push_back(Neptune);
        _planets.push_back(Pluto);
    }

    void Sun::drawSystem(float t, Camera* camera){
        //bind
        _programSun.m_Program.use();
        glBindTexture(GL_TEXTURE_2D,_textureSun);
        glUniform1i(_programSun.uTexture, 0);
        glBindVertexArray(_vao);
        /*to do camera*/
        glm::mat4 viewMatrix = camera->getViewMatrix();
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5)) * viewMatrix;
        MVMatrix = glm::rotate(MVMatrix, t/1.0f, glm::vec3(0, 1, 0));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programSun.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programSun.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programSun.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*_sphere.getVertexCount());
        glBindVertexArray(0);
        
        for (auto planet : _planets) {
            planet->drawPlanet(_diameter,_rotation, _sphere.getVertexCount(),t, camera);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void Sun::drawOnePlanet(int numPlanet, float t, Camera* camera){
		_planets[numPlanet]->drawPlanetAlone(_rotation,_sphere.getVertexCount(), t, _vao, camera);
	}
    
    void Sun::deleteTextures(){
        glDeleteTextures(1,&_textureSun);
        for(auto planet : _planets){
            planet->deleteTextures();
        }
    }
}
