#pragma once
#include "Moon.hpp"
#include "PlanetProgram.hpp"
#include <glimac/Sphere.hpp>
#include <list>

namespace glimac {
    class Planet{
        private:
            GLuint _texturePlanet;
            GLuint _textureExtra;
            PlanetProgram _programPlanet;
            std::unique_ptr<Image> _imgPlanet;
            std::unique_ptr<Image> _imgExtra;
            std::list<Moon*> _moons;
            Ellipse _ellipse;
            
            GLuint _vbo;
            GLuint _vao;
            Sphere _sphere;
                        
            bool _extra;
            bool _rings;
            float _aphelion;
            float _perihelion;
            float _eccentricity;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;
            
            void initVboVao();
            void initTexture();
            void initTextureExtra();

        public:
          	Planet() : _sphere(Sphere(log10(1.0f)/2.0f, 32, 16)){}
          	Planet(Planet const&) : _sphere(Sphere(log10(1.0f)/2.0f, 32, 16)){}
            Planet(char* path, std::string pathImg, std::string pathImg2, std::list<Moon*> moons, bool extra, bool rings, float aphelion, float perihelion, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination, float sunDiameter, float eccentricity, int num):
            _moons(moons),_aphelion(aphelion), _perihelion(perihelion), _extra(extra), _rings(rings), _diameter(log10(diameter)), _orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(glm::radians(orbitalInclination)), _eccentricity(eccentricity), _sphere(Sphere(log10(diameter/2.0f), 32, 16)){
                FilePath applicationPath(path);
                _programPlanet = {applicationPath, extra};
                _imgPlanet = loadImage(pathImg);
                _ellipse = Ellipse(path,_perihelion, _aphelion, _eccentricity, _orbitalInclination, num);
                this->initVboVao();
                this->initTexture();
                if(_extra){
                    _imgExtra = loadImage(pathImg2);
                    this->initTextureExtra();
                }
            }
            
            void drawPlanet(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera);
            void drawPlanetRing(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera);
            void drawPlanetExtra(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera);
            void drawSimplePlanet(float sunDiameter, GLuint vao, float nb_vertex, float t, Camera* camera);
            
            void drawPlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t,  Camera* camera);
            void drawPlanetRingAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            void drawPlanetExtraAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            void drawSimplePlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            
            void deleteTextures();
    };
}
