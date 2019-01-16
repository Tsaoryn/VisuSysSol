#pragma once
#include <glimac/Sphere.hpp>
#include <glimac/Ellipse.hpp>
#include <glimac/Image.hpp>
#include "GeneralProgram.hpp"

namespace glimac {
    class SphereDrawer{
        private:
            GLuint _vbo;
            GLuint _vao;
            
            Sphere _sphere;
            float nb_vertices;
            
            GLuint _textureOne;
            GLuint _textureTwo;

            GeneralProgram _program;
            std::unique_ptr<Image> _imgOne;
            std::unique_ptr<Image> _imgTwo;
            
            void initVboVao();
            void initTexture();
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
            
            int getNbVertices();
            void drawPlanet(float t, Camera* camera, bool toTranslate, bool _extra, float _lengthDays, float scaleValue, glm::vec3 vec = glm::vec3(0,0,0));
            void deleteTextures(bool _extra);
    };
}
