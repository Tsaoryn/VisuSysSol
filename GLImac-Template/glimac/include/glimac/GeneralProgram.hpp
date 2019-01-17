#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
    /* sert à contenir le programme et les identifiants des matrices à envoyer aux shaders 
    *  est utilisé seulement par les classes contenant une sphere
    */
    class GeneralProgram{
        public:
            Program m_Program;
            GLint uMVPMatrix;
            GLint uMVMatrix;
            GLint uNormalMatrix;
            GLint uTexture;
            GLint uExtraTexture;
            
            GeneralProgram(){}
            
            GeneralProgram(const FilePath& applicationPath, bool extra){
                // cas où la sphere a besoin de deux textures (ex : la Terre)
                if(extra==true){
                    m_Program = Program(loadProgram(applicationPath.dirPath() + "/shaders/3D.vs.glsl",
                                      applicationPath.dirPath() + "/shaders/multiTex3D.fs.glsl"));
                    uExtraTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
                }
                // cas où la planete n'a besoin que d'une texture
                else
                    m_Program = Program(loadProgram(applicationPath.dirPath() + "/shaders/3D.vs.glsl",
                                      applicationPath.dirPath() + "/shaders/tex3D.fs.glsl"));
            	uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            	uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            	uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            	uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        	}
    };
}
