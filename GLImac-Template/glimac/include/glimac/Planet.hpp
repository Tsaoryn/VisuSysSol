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

            std::string _name;
            bool _extra;
            bool _rings;
            float _aphelion;
            float _perihelion;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;
            
            void initTexture();
            void initTextureExtra();
            //void initPlanet(std::string name);
            //void initMoonList(string name, char* path);

        public:
          	Planet(){}
          	Planet(Planet const&){}
            Planet(std::string name, char* path, std::string pathImg, std::string pathImg2, bool extra, bool rings, float aphelion, float perihelion, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination) : _name(name), _extra(extra), _rings(rings), _aphelion(aphelion), _perihelion(perihelion), _diameter(diameter), _orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(orbitalInclination){
                //initPlanet(name);
                //initMoonList(name, path);

                FilePath applicationPath(path);
                _programPlanet = {applicationPath};
                _imgPlanet = loadImage(pathImg);
                this->initTexture();

                if(_extra){
                    _imgExtra = loadImage(pathImg2);
                    this->initTextureExtra();
                }
            }
            
            void drawPlanet(float sunDiameter, float sunRotation, float nb_vertex, float t);
            void drawPlanetRing(float sunDiameter, float sunRotation, float nb_vertex, float t);
            void drawPlanetExtra(float sunDiameter, float sunRotation, float nb_vertex, float t);
            void drawSimplePlanet(float sunDiameter, float sunRotation, float nb_vertex, float t);
            
            void deleteTextures();
    };
}
