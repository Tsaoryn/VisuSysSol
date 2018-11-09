#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
    class SunProgram{
        public:
            Program m_Program;
            GLint uMVPMatrix;
            GLint uMVMatrix;
            GLint uNormalMatrix;
            GLint uTexture;
            
            SunProgram(SunProgram const&);
            
            SunProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "../../../VisuSysSol/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "../../../VisuSysSol/shaders/tex3D.fs.glsl")) {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        }
    };
}
