#pragma once
#include <glimac/Sphere.hpp>
#include <glimac/Ellipse.hpp>
#include <glimac/Image.hpp>
#include "GeneralProgram.hpp"
#include <memory>

namespace glimac {
    /* classe de dessin des spheres */
    class SphereDrawer{
        private:
            GLuint _vbo;
            GLuint _vao;
            GLuint _ibo;
            
            Sphere _sphere;
            float nb_vertices;
            
            GLuint _textureOne;
            GLuint _textureTwo;

            GeneralProgram _program;
            std::shared_ptr<Image> _imgOne;
            std::shared_ptr<Image> _imgTwo;
            
            // initialise le vbo et le vao de l'ellipse
            void initVboVao();
            // initialise la première texture
            void initTexture();
            // initialise la deuxieme texture si besoin
            void initTextureExtra();

        public:
            SphereDrawer(){}
            SphereDrawer(char* path, std::string pathImg, std::string pathImg2, float sphereDiameter, bool rings, bool extra) : _sphere(Sphere(log10(sphereDiameter/2.0f), 32, 16)){
                FilePath applicationPath(path);
                
                _program = {applicationPath, extra};
                _imgOne = loadImage(pathImg);
                nb_vertices = _sphere.getVertexCount();
                this->initTexture();
                
                if(rings){
				}
                else if(extra){
                    _imgTwo = loadImage(pathImg2);
                    this->initTextureExtra();
                }
                this->initVboVao();
            }
            // Retourne le nombre de sommet de la sphere
            int getNbVertices();
            // dessine la planete
            void drawPlanet(float t, std::shared_ptr<Camera> camera, bool toTranslate, bool _extra, float _lengthDays, float scaleValue, glm::vec3 vec = glm::vec3(0,0,0));
            // suprime la texture liée à la planete
            void deleteTextures(bool _extra);
    };
}
