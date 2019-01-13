#pragma once
#include "Moon.hpp"
#include "PlanetProgram.hpp"
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
            
            bool _extra;
            bool _rings;
            float _aphelion;
            float _perihelion;
            float _eccentricity;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;
            
            void initTexture();
            void initTextureExtra();

        public:
          	Planet(){}
          	Planet(Planet const&){}
            Planet(char* path, std::string pathImg, std::string pathImg2, std::list<Moon*> moons, bool extra, bool rings, float aphelion, float perihelion, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination, float sunDiameter):
            _moons(moons),_aphelion(log10(aphelion)), _perihelion(log10(perihelion)), _extra(extra), _rings(rings), _diameter(log10(diameter)), _orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(glm::radians(orbitalInclination)){
                FilePath applicationPath(path);
                _programPlanet = {applicationPath, extra};
                _imgPlanet = loadImage(pathImg);
                _eccentricity = -1*((_perihelion / ((aphelion+perihelion)/2))-1);
                _ellipse = Ellipse(path,perihelion, aphelion, _eccentricity, orbitalInclination);
                this->initTexture();
                if(_extra){
                    _imgExtra = loadImage(pathImg2);
                    this->initTextureExtra();
                }
            }
            
            void drawPlanet(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            void drawPlanetRing(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            void drawPlanetExtra(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            void drawSimplePlanet(float sunDiameter, float sunRotation, float nb_vertex, float t, Camera* camera);
            
            void drawPlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, GLuint vao, Camera* camera);
            void drawPlanetRingAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, GLuint vao, Camera* camera);
            void drawPlanetExtraAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, GLuint vao, Camera* camera);
            void drawSimplePlanetAlone(float sunDiameter, float sunRotation, float nb_vertex, float t, GLuint vao, Camera* camera);
            
            void deleteTextures();
    };
}
