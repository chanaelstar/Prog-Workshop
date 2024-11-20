#include <sil/sil.hpp>

float brightness(glm::vec3 const&color){
    float gray = color.r * 0.21 + color.g *0.72 + color.b * 0.07;

    return gray;
}