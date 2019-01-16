#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
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
                if(extra==true){
                    m_Program = Program(loadProgram(applicationPath.dirPath() + "/shaders/3D.vs.glsl",
                                      applicationPath.dirPath() + "/shaders/multiTex3D.fs.glsl"));
                    uExtraTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
                }
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
