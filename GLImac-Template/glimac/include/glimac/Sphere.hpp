#pragma once

#include <vector>
#include <iostream>
#include "common.hpp"

namespace glimac {

/* Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local) */
/* Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1) */
class Sphere {
    // Alloue et construit les données
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

    private:
        std::vector<ShapeVertex> m_Vertices;
        std::vector<uint32_t> indicesIbo;
        GLsizei m_nVertexCount; // Nombre de sommets

    public:
        Sphere(){}
        Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong):
            m_nVertexCount(0) {
            build(radius, discLat, discLong);
        }

        // Retourne un pointeur vers la liste des sommets sans duplication
        const ShapeVertex* getDataPointer() const {
            return &m_Vertices[0];
        }
        // Retourne un pointeur vers la liste des indices pour l'ibo
        const uint32_t* getIndicesPointer() const {
            return &indicesIbo[0];
        }
        // Retourne la taille d ela liste de sommet pour l'ibo
        GLsizei getVerticesCount() const {
            return indicesIbo.size();
        }
        // Retourne le nombre de sommets de la sphere
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }
};
    
}
