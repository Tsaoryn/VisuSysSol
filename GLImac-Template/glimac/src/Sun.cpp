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
        //débind
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
    
    void Sun::initPlanets(PlanetProgram programPlanet, MoonProgram programMoon){
        //don't forget to change subPath when you change your installation
        std::list<Moon> moons = {};
        std:string subPath = "/home/2ins2/ksadki01/Documents/synthese/VisuSysSol/GLImac-Template";
        
        std::string pathMoon = subPath+"/assets/textures/MoonMap.jpg";
        Moon moon = {"Moon",pathMoon,384400.0f+0.0549f,3475.0f,5.145f,programMoon};
        Moon Phobos = {"Phobos",pathMoon,9378.0f+0.0151f,22.5f,1.08f,programMoon};
        Moon Demios = {"Demios",pathMoon,23459.0f+0.0005f,12.0f,1.79f,programMoon};
        Moon Callisto = {"Callisto",pathMoon,1882710.0f+0.007f,4821.0f,0.19f,programMoon};
        Moon Ganymede = {"Ganymede",pathMoon,1070410.0f+0.001f,5262.0f,0.18f,programMoon};
        Moon Europa = {"Europa",pathMoon,671030.0f+0.009f,3122.0f,0.47f,programMoon};
        Moon Io = {"Io",pathMoon,421700.0f+0.004f,3643.0f,0.04f,programMoon};
        Moon Mimas = {"Mimas",pathMoon,185520.0f+0.0202f,392.0f,1.53f,programMoon};
        Moon Enceladus = {"Enceladus",pathMoon,238020.f+0.0045f,498.0f,0.0f,programMoon};
        Moon Tethys = {"Tethys",pathMoon,294660.0f+0.0f,1060.0f,1.86f,programMoon};
        Moon Dione = {"Dione",pathMoon,377400.0f+0.0022f,1120.0f,0.02f,programMoon};
        Moon Rhea = {"Rhea",pathMoon,527040.0f+0.0010f,1530.0f,0.35f,programMoon};
        Moon Titan = {"Titan",pathMoon,1221830.0f+0.0292f,5150.0f,0.33f,programMoon};
        Moon Hyperion = {"Hyperion",pathMoon,1481100.0f+0.1042f,286.0f,0.43f,programMoon};
        Moon Iapetus = {"Iapetus",pathMoon,3561300.0f+0.0283f,1460.0f,14.72f,programMoon};
        Moon Ariel = {"Ariel",pathMoon,199900.0f+0.0012f,1158.0f,0.04f,programMoon};
        Moon Umbriel = {"Umbriel",pathMoon,266000.0f+0.0039f,1169.0f,0.13f,programMoon};
        Moon Titania = {"Titania",pathMoon,436300.0f+0.0011f,1577.0f,0.08,programMoon};
        Moon Oberon = {"Oberon",pathMoon,583500.0f+0.0014,1523.0f,0.07f,programMoon};
        Moon Miranda = {"Miranda",pathMoon,129900.0f+0.0013,472.0f,4.34f,programMoon};
        Moon Triton = {"Triton",pathMoon,354760.0f+0.000016f,2707.0f,157.345f,programMoon};
        Moon Nereid = {"Nereid",pathMoon,5513400.0f+0.7512,340.0f,7.23f,programMoon};
        Moon Charon = {"Charon",pathMoon,19591.0f+0.0f,1212.0f,0.00005f,programMoon};
                
        Planet Mercury = {subPath+"/assets/textures/MercuryMap.jpg", "", moons, false, false,69800000.0f/46000000.0f, 4879.0f, 88.0f, 4222.6f,7.0f,programPlanet};
        Planet Venus = {subPath+"/assets/textures/VenusMap.jpg", "", moons, false, false,108900000.0f/107500000.0f, 12104.0f, 224.7f, 2802.0f,3.4f,programPlanet};
        moons.push_back(moon);
        Planet Earth = {subPath+"/assets/textures/EarthMap.jpg", subPath+"/assets/textures/CloudMap", moons, true, false,152100000.0f/147100000.0f, 12756.0f, 365.2f,24.0f,0.0f,programPlanet};
        moons.clear();
        moons.push_back(Phobos);
        moons.push_back(Demios);
        Planet Mars = {subPath+"/assets/textures/MarsMap.jpg", "", moons, false, false,249200000.0f/206600000.0f, 6792.0f, 687.0f,24.7f,1.9f,programPlanet };
        moons.clear();
        moons.push_back(Callisto);
        moons.push_back(Ganymede);
        moons.push_back(Europa);
        moons.push_back(Io);
        Planet Jupiter = {subPath+"/assets/textures/JupiterMap.jpg", "", moons, false, false,816600000.0f/740500000.0f, 142984.0f,4331.0f,9.9f,1.3f,programPlanet };
        moons.clear();
        moons.push_back(Mimas);
        moons.push_back(Enceladus);
        moons.push_back(Tethys);
        moons.push_back(Dione);
        moons.push_back(Rhea);
        moons.push_back(Titan);
        moons.push_back(Hyperion);
        moons.push_back(Iapetus);
        Planet Saturn = {subPath+"/assets/textures/SaturnMap.jpg", subPath+"/assets/textures/saturnringcolor.jpg", moons, true, true, 1514500000.0f/1352600000.0f, 120536.0f, 10747.0f,10.7f,2.5f,programPlanet };
        moons.clear();
        moons.push_back(Ariel);
        moons.push_back(Umbriel);
        moons.push_back(Titania);
        moons.push_back(Oberon);
        moons.push_back(Miranda);
        Planet Uranus = {subPath+"/assets/textures/UranusMap.jpg", subPath+"/assets/textures/uranusringcolor.jpg", moons, true, true,3003600000.0f/2741300000.0f, 51118.0f, 30589.0f,17.2f, 0.8f,programPlanet };
        moons.clear();
        moons.push_back(Triton);
        moons.push_back(Nereid);
        Planet Neptune = {subPath+"/assets/textures/NeptuneMap.jpg", "", moons, false, false,4545700000.0f/4444500000.0f, 49528.0f, 59800.0f,16.1f,1.8f,programPlanet };
        moons.clear();
        moons.push_back(Charon);
        Planet Pluto = {subPath+"/assets/textures/PlutoMap.jpg", "", moons, false, false,7375900000.0f /4436800000.0f, 2370.0f, 90560.0f,153.3f,17.2f,programPlanet };
		
		_planets.insert( std::pair<std::string,Planet>("Mercury",Mercury) );
		_planets.insert( std::pair<std::string,Planet>("Venus",Venus) );
		_planets.insert( std::pair<std::string,Planet>("Earth",Earth) );
		_planets.insert( std::pair<std::string,Planet>("Mars",Mars) );
		_planets.insert( std::pair<std::string,Planet>("Jupiter",Jupiter) );
		_planets.insert( std::pair<std::string,Planet>("Saturn",Saturn) );
		_planets.insert( std::pair<std::string,Planet>("Uranus",Uranus) );
		_planets.insert( std::pair<std::string,Planet>("Neptune",Neptune) );
		_planets.insert( std::pair<std::string,Planet>("Pluto",Pluto) );
		
    }

    void Sun::drawSystem(){
        //bind
        glBindTexture(GL_TEXTURE_2D,_textureSun);
        _programSun.m_Program.use();
        glUniform1i(_programSun.uTexture, 1);
        glBindVertexArray(_vao);
        /*to do camera*/
        glm::mat4 viewMatrix = glm::mat4(1.0f);
    
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1000.f/1000.f,0.1f,100.f)* viewMatrix;
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0)) * viewMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix)) * viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
    
        glUniformMatrix4fv(_programSun.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programSun.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programSun.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
    
        
        glDrawArrays(GL_TRIANGLES, 0, 8*_sphere.getVertexCount());
        glBindVertexArray(0);
    }
    
    void Sun::deleteTextures(){
        glDeleteTextures(1,&_textureSun);
        for(map<string, Planet>::iterator it = _planets.begin(); it!=_planets.end(); ++it){
            (it->second).deleteTextures();
        }
    }
}
