#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
    class PlanetProgram{
        public:
            Program m_Program;
            GLint uMVPMatrix;
            GLint uMVMatrix;
            GLint uNormalMatrix;
            GLint uPlanetTexture;
            GLint uExtraTexture;
            
            PlanetProgram(){}
            
            PlanetProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/tex3D.fs.glsl")) {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uPlanetTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
            uExtraTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
        }
    };
}
