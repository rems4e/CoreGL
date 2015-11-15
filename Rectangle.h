//
//  Rectangle.h
//  Projet2MIC
//
//  Créé par Marc Promé et Rémi Saurel.
//  Ce fichier et son contenu sont librement distribuables, modifiables et utilisables pour toute
//  œuvre non commerciale,
//  à condition d'en citer les auteurs.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <algorithm>
#include "Geometry.h"

namespace CoreGL {

    struct Box {
        Box() = default;
        Box(vec3 const &o, vec3 const &dim)
                : origin(o)
                , size(dim) {}

        bool intersection(Box const &b) const;

        vec3 origin;
        vec3 size;
    };

    struct Rectangle {
        coordinate_t left, top;
        dimension_t width, height;

        Rectangle()
                : left{}
                , top{}
                , width{}
                , height{} {}
        Rectangle(coordinate_t const &g, coordinate_t const &h, dimension_t const &la, dimension_t const &ha)
                : left(g)
                , top(h)
                , width(la)
                , height(ha) {}
        Rectangle(vec2 const &origine, vec2 const &taille)
                : left(origine.x)
                , top(origine.y)
                , width(taille.x)
                , height(taille.y) {}
        Rectangle(Rectangle const &r, int)
                : left(0)
                , top(0)
                , width(r.width)
                , height(r.height) {}

        Rectangle &setOrigin(vec2 const &c) {
            left = c.x, top = c.y;
            return *this;
        }
        Rectangle &setSize(vec2 const &c) {
            width = c.x, height = c.y;
            return *this;
        }

        vec2 origine() const {
            return vec2(left, top);
        }
        vec2 size() const {
            return vec2(width, height);
        }

        Rectangle &shift(vec2 const &vec) {
            left += vec.x;
            top += vec.y;

            return *this;
        }

        bool contains(vec2 const &p) const {
            return Rectangle(p, vec2(0.0)) < *this;
        }

        bool operator==(Rectangle const &r) const {
            return left == r.left && top == r.top && width == r.width && height == r.height;
        }
        bool operator!=(Rectangle const &r) const {
            return !(*this == r);
        }

        bool operator<(Rectangle const &r) const { // Inclusion stricte dans r
            return left >= r.left && top >= r.top && left + width <= r.left + r.width &&
                   top + height <= r.top + r.height && *this != r;
        }
        bool operator<=(Rectangle const &r) const { // Inclusion dans r
            return *this < r || *this == r;
        }

        bool empty() const {
            return Geometry::nullValue(width * height);
        }

        Rectangle intersection(Rectangle const &r2) const {
            Rectangle retour;
            retour.left = std::max(left, r2.left);
            retour.top = std::max(top, r2.top);
            retour.width = std::min(left + width - retour.left, r2.left + r2.width - retour.left);
            retour.height = std::min(top + height - retour.top, r2.top + r2.height - retour.top);
            if(retour.width < 0 || retour.height < 0)
                retour = Rectangle();

            return retour;
        }

        Rectangle unionRect(Rectangle const &r2) const {
            Rectangle retour;
            retour.left = std::min(left, r2.left);
            retour.top = std::min(top, r2.top);
            retour.width = std::max(left + width - retour.left, r2.left + r2.width - retour.left);
            retour.height = std::max(top + height - retour.top, r2.top + r2.height - retour.top);

            return retour;
        }

        bool superposition(Rectangle const &r2) const {
            return ((left >= r2.left && left < r2.left + r2.width) ||
                    (left < r2.left && left + width > r2.left)) &&
                   ((top >= r2.top && top < r2.top + r2.height) || (top < r2.top && top + height > r2.top));
        }
    };


    std::ostream &operator<<(std::ostream &s, Rectangle const &r);
}

#endif
