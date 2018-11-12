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
            std::list<Moon> _moons;
            
            bool _extra;
            bool _rings;
            float _ellipse;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;
            
            void initTexture();
            void initTextureExtra();
        public:
            Planet(Planet const&){}
            
            Planet(){}
        
            Planet(char* path, std::string pathImg, std::string pathImg2, std::list<Moon> moons, bool extra, bool rings, float ellipse, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination):
            _moons(moons),_ellipse(ellipse), _extra(extra), _rings(rings), _diameter(diameter), _orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(orbitalInclination){
                FilePath applicationPath(path);
                _programPlanet = {applicationPath};
                _imgPlanet = loadImage(pathImg);
                this->initTexture();
                
                if(_extra){
                    _imgExtra = loadImage(pathImg2);
                    this->initTextureExtra();
                }
            }
            
            void deleteTextures();
    };
}
