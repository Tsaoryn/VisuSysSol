#pragma once
#include <vector>
#include "EllipseProgram.hpp"
#include "common.hpp"
#include "glimac/Camera.hpp"
#include <math.h>
#include <memory>

namespace glimac {

/* Classe servant à représenter les ellipses des planètes et des lunes */
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
        
        float a; // rayon majeur de l'ellipse
        float b; // rayon mineur de l'ellipse
        int _additionalNum; // nombre permettant d'augmenter la taille de l'ellipse afin de rendre la distance entre les orbites visuellement plus realiste
        
        // initialise les points de l'ellipse
        void initVertices();
        // initialise le vbo et le vao de l'ellipse
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
        
        // renvoie le vecteur de translation de l'origine au point en fonction de l'angle donné
        glm::vec3 translationVector(float angle);
        // dessine l'ellipse
        void draw(std::shared_ptr<Camera> camera);
    };
}
