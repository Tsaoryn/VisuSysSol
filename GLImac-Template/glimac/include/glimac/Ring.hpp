#pragma once
#include <vector>
#include "EllipseProgram.hpp"
#include "common.hpp"
#include "glimac/Camera.hpp"
#include <glimac/Image.hpp>
#include <math.h>

namespace glimac {
/* classe incomplète qui aurait du représenter les anneaux de Saturne et Uranus */
class Ring {
    private:
        GLuint _vbo;
        GLuint _vao;
        std::unique_ptr<Image> _imgRing;
        MoonProgram _programMoon;
        
        float _planetDiameter;
        float _radiusRing;
        
        void initVertices();
        void initVboVao();
    public:
        Ring(){}
    
        Ring(char* path, float radiusRing, float diameter,std::unique_ptr<Image> img) : 
        _planetDiameter(diameter), _radiusRing(radiusRing){
            FilePath applicationPath(path);
            _programMoon = {applicationPath};
            this->initVertices();
            this->initVboVao();
        }
        // dessine l'anneau
        void draw(Camera* camera);
    };
}
