#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
    class MoonProgram{
        public:
            Program m_Program;
            GLint uMVPMatrix;
            GLint uMVMatrix;
            GLint uNormalMatrix;
            GLint uMoonTexture;
            
            MoonProgram(MoonProgram const&);
            
            MoonProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "../../../VisuSysSol/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "../../../VisuSysSol/shaders/tex3D.fs.glsl")) {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uMoonTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        }
    };
}
