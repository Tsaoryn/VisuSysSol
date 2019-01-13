#pragma once
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
using namespace std;

namespace glimac {
    class EllipseProgram{

        public:
            Program m_Program;
            GLint uMVPMatrix;
            GLint uMVMatrix;
            GLint uNormalMatrix;
            
            EllipseProgram(){}
            
            EllipseProgram(const FilePath& applicationPath):
            	m_Program(loadProgram(applicationPath.dirPath() + "/shaders/Ellipse.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/Ellipse.fs.glsl")) {
            		uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            		uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            		uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
       			}
    };
}
