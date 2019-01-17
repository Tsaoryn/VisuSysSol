#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "glm.hpp"
#include "FilePath.hpp"

namespace glimac {
/* classe représentant les textures des planètes et des lunes */
/* classe fournie lors des TP */
class Image {
    private:
        unsigned int m_nWidth = 0u;
        unsigned int m_nHeight = 0u;
        std::unique_ptr<glm::vec4[]> m_Pixels;

    public:
        Image(unsigned int width, unsigned int height):
            m_nWidth(width), m_nHeight(height), m_Pixels(new glm::vec4[width * height]) {
        }
        // retourne la largeur de l'image
        unsigned int getWidth() const {
            return m_nWidth;
        }
        // retourne la hauteur de l'image
        unsigned int getHeight() const {
            return m_nHeight;
        }
        // retourne la matrice de pixels de l'image
        const glm::vec4* getPixels() const {
            return m_Pixels.get();
        }
        // retourne la matrice de pixels de l'image
        glm::vec4* getPixels() {
            return m_Pixels.get();
        }
};

std::unique_ptr<Image> loadImage(const FilePath& filepath);

class ImageManager {
    private:
        static std::unordered_map<FilePath, std::unique_ptr<Image>> m_ImageMap;

    public:
        // charge l'image
        static const Image* loadImage(const FilePath& filepath);
};

}
