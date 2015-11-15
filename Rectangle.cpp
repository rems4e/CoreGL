//
//  Rectangle.cpp
//  Projet2MIC
//
//  Créé par Marc Promé et Rémi Saurel.
//  Ce fichier et son contenu sont librement distribuables, modifiables et utilisables pour toute
//  œuvre non commerciale,
//  à condition d'en citer les auteurs.
//

#include "Rectangle.h"
#include <iostream>

namespace CoreGL {
    std::ostream &operator<<(std::ostream &s, Rectangle const &r) {
        return s << "{(" << r.left << ", " << r.top << "), (" << r.width << ", " << r.height
                 << ")}";
    }

    bool Box::intersection(Box const &b) const {
        vec3 ecart = glm::abs(b.origin - this->origin) - (b.size + this->size) / 2;

        return ecart.x <= 0 && ecart.y <= 0 && ecart.z <= 0;
    }
}
