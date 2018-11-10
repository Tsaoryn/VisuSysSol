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
        GLuint vbo;
        glGenBuffers(1, &vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        const ShapeVertex * vertices = _sphere.getDataPointer();
        
        glBufferData(GL_ARRAY_BUFFER, nb_floats*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        /*vao*/
        GLuint vao;
        glGenVertexArrays(1, &vao);
        
        glBindVertexArray(vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION_SHADER);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL_SHADER);
        glEnableVertexAttribArray(VERTEX_ATTR_TEX_SHADER);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glVertexAttribPointer(VERTEX_ATTR_POSITION_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) 0);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL_SHADER, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) (3*sizeof(GLfloat)));
        glVertexAttribPointer(VERTEX_ATTR_TEX_SHADER, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(const GLvoid*) (6*sizeof(GLfloat)));
        
        //débind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//GL_FILL
    }
    
    void Sun::initPlanets(PlanetProgram programPlanet, MoonProgram programMoon){
        //don't forget to change the absolute path when you change your installation
        std::list<Moon> moons = {};
        std::string pathMoon = "/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MoonMap";
        Moon moon = {"Moon",pathMoon,384400.0f+0.0549f,3475.0f,5.145f,programMoon};
        Moon Phobos = {"Phobos",pathMoon,9378.0f+0.0151f,22.5f,1.08f,programMoon};
        Moon Demios = {"Demios",pathMoon,23459.0f+0.0005f,12.0f,1.79f,programMoon};
        Moon Callisto = {"Callisto",pathMoon,1882710.0f+0.007f,4821.0f,0.19f,programMoon};
        Moon Ganymède = {"Ganymède",pathMoon,1070410.0f+0.001f,5262.0f,0.18f,programMoon};
        Moon Europa = {"Europa",pathMoon,671030.0f+0.009f,3122.0f,0.47f,programMoon};
        Moon Io = {"Io",pathMoon,421700f+0.004f,3643.0f,0.04f,programMoon};
        Moon Mimas = {"Mimas",pathMoon,185520.0f+0.0202f,392.0f,1.53f,programMoon};
        Moon Enceladus = {"Enceladus",pathMoon,238020.f+0.0045f,498.0f,0.0f,programMoon};
        Moon Tethys = {"Tethys",pathMoon,294660.0f+0.0f,1060.0f,1.86f,programMoon};
        Moon Dione = {"Dione",pathMoon,377400.0f+0.0022f,1120.0f,0.02f,programMoon};
        Moon Rhea = {"Rhea",pathMoon,527040.0f+0.0010f,1530.0f,0.35f,programMoon};
        Moon Titan = {"Titan",pathMoon,1221830.0f+0.0292f,5150.0f,0.33f,programMoon};
        Moon Hyperion = {"Hyperion",pathMoon,1481100.0f+0.1042f,286.0f,0.43f,programMoon};
        Moon Iapetus = {"Iapetus",pathMoon,3561300.0f+0.0283f,1460.0f,14.72f,programMoon};
        Moon Ariel = {"Ariel",pathMoon,,,,programMoon};
        Moon Umbriel = {"Umbriel",pathMoon,,,,programMoon};
        Moon Titania = {"Titania",pathMoon,,,,programMoon};
        Moon Obéron = {"Obéron",pathMoon,,,,programMoon};
        Moon Miranda = {"Miranda",pathMoon,,,,programMoon};
        Moon Triton = {"Triton",pathMoon,,,,programMoon};
        Moon Nereid = {"Nereid",pathMoon,,,,programMoon};
        Moon Charon = {"Charon",pathMoon,,,,programMoon};
                
        Planet Mercury = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        Planet Venus = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.push_back(moon);
        Planet Earth = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Phobos);
        moons.push_back(Demios);
        Planet Mars = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Callisto);
        moons.push_back(Ganymède);
        moons.push_back(Europa);
        moons.push_back(Io);
        Planet Jupiter = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Mimas);
        moons.push_back(Enceladus);
        moons.push_back(Tethys);
        moons.push_back(Dione);
        moons.push_back(Rhea);
        moons.push_back(Titan);
        moons.push_back(Hyperion);
        moons.push_back(Iapetus);
        Planet Saturn = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Ariel);
        moons.push_back(Umbriel);
        moons.push_back(Titania);
        moons.push_back(Obéron);
        moons.push_back(Miranda);
        Planet Uranus = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Triton);
        moons.push_back(Nereid);
        Planet Neptune = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
        moons.clear();
        moons.push_back(Charon);
        Planet Pluto = {"/home/karim/Bureau/karim/VisuSysSol/VisuSysSol/GLImac-Template/assets/textures/MercuryMap", "", };
    }
}
