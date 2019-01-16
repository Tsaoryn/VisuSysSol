#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {

	void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong) {
		// Equation paramétrique en (r, phi, theta) de la sphère 
		// avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= phi <= 2PI
		//
		// x(r, phi, theta) = r sin(phi) cos(theta)
		// y(r, phi, theta) = r sin(theta)
		// z(r, phi, theta) = r cos(phi) cos(theta)
		//
		// Discrétisation:
		// dPhi = 2PI / discLat, dTheta = PI / discLong
		//
		// x(r, i, j) = r * sin(i * dPhi) * cos(-PI / 2 + j * dTheta)
		// y(r, i, j) = r * sin(-PI / 2 + j * dTheta)
		// z(r, i, j) = r * cos(i * dPhi) * cos(-PI / 2 + j * dTheta)

		GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
		GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;
		
		std::vector<ShapeVertex> data;
		
		// Construit l'ensemble des vertex
		for(GLsizei j = 0; j <= discLong; ++j) {
			GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
			GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);
			
			for(GLsizei i = 0; i <= discLat; ++i) {
				ShapeVertex vertex;
				
				vertex.texCoords.x = i * rcpLat;
				vertex.texCoords.y = 1.f - j * rcpLong;

				vertex.normal.x = sin(i * dPhi) * cosTheta;
				vertex.normal.y = sinTheta;
				vertex.normal.z = cos(i * dPhi) * cosTheta;
				
				vertex.position = r * vertex.normal;
				
				m_Vertices.push_back(vertex);
			}
		}

		m_nVertexCount = discLat * discLong * 6;
		
		GLuint idx = 0;
	   
		for(uint32_t j = 0; j < discLong; ++j) {
			uint32_t offset = j * (discLat + 1);
			for(uint32_t i = 0; i < discLat; ++i) {
				indicesIbo.push_back(offset + i);
				indicesIbo.push_back(offset + (i + 1));
				indicesIbo.push_back(offset + discLat + 1 + (i + 1));
				indicesIbo.push_back(offset + i);
				indicesIbo.push_back(offset + discLat + 1 + (i + 1));
				indicesIbo.push_back(offset + i + discLat + 1);
			}
		}
	}

}
