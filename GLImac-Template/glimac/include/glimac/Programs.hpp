#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

namespace glimac{
    struct PlanetProgram {
        Program m_Program;

        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uPlanetTexture;
        GLint uExtraTexture;
        
        PlanetProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "../../../VisuSysSol/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "../../../VisuSysSol/shaders/multiTex3D.fs.glsl")) {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uPlanetTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
            uExtraTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture2");
        }
    };

    struct SunProgram {
        Program m_Program;

        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uTexture;

        SunProgram(const FilePath& applicationPath):
            m_Program(loadProgram(applicationPath.dirPath() + "../../../VisuSysSol/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "../../../VisuSysSol/shaders/tex3D.fs.glsl")) {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        }
    };
    
    struct MoonProgram {
        Program m_Program;

        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uMoonTexture;
        
        MoonProgram() = default; 
        
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
