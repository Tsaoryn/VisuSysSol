#pragma once
#include <vector>
#include "EllipseProgram.hpp"
#include "common.hpp"
#include "glimac/Camera.hpp"
#include <math.h>

namespace glimac {

class Ellipse {
    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount;
        GLuint _vbo;
        GLuint _vao;
        EllipseProgram _programEllipse;
        
        float _perihelion;
        float _aphelion;
        float _eccentricity;
        float _inclination;
        float a;
        float b;
        int _additionalNum;
        
        void initVertices();
        void initVboVao();
    public:
        Ellipse(){}
    
        Ellipse(char* path, float perihelion, float aphelion, float eccentricity, float inclination, int num) : 
        _perihelion(perihelion), _aphelion(aphelion), _eccentricity(eccentricity), _inclination(inclination), _additionalNum(num){
            FilePath applicationPath(path);
            _programEllipse = {applicationPath};
            
            a = log10((_aphelion+_perihelion)/2.0f)+_additionalNum;
            b = log10(((_aphelion+_perihelion)/2.0f)*std::sqrt(1-(_eccentricity*_eccentricity)))+_additionalNum;
            
            this->initVertices();
            this->initVboVao();
        }
        
        glm::vec3 translationVector(float angle);
        void draw(Camera* camera);
        
    };
}
