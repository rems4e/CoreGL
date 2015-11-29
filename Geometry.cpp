//
//  Geometry.cpp
//  CoreGL
//
//  Created by Rémi on 07/06/08.
//  Additional contributor (2012): Marc Promé
//


#include "Geometry.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace CoreGL {

    namespace Geometry {
        mat4 perspective(float angle, float ratio, float near, float far) {
            return glm::perspective(angle, ratio, near, far);
        }

        mat4 translate(vec3 const &vec) {
            return glm::translate(mat4(), vec);
        }

        mat4 scale(vec3 const &vec) {
            return glm::scale(mat4(), vec);
        }

        mat4 rotate(float angle, vec3 vec) {
            return glm::rotate(mat4(), angle, vec);
        }

        mat4 camera(vec3 const &position, vec3 const &target, vec3 const &up) {
            return glm::lookAt(position, target, up);
        }

        mat4 cameraSphere(vec3 const &relativeToSphere, vec3 const &target, vec3 const &up) {
            vec3 cartesianDirection = Geometry::sphericToCartesian(relativeToSphere);
            return camera(cartesianDirection + target, target, up);
        }
    }
}

std::ostream &operator<<(std::ostream &s, glm::vec4 const &c) {
    return s << '(' << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ')';
}

std::ostream &operator<<(std::ostream &s, glm::vec3 const &c) {
    return s << '(' << c.x << ", " << c.y << ", " << c.z << ')';
}

std::ostream &operator<<(std::ostream &s, glm::vec2 const &c) {
    return s << '(' << c.x << ", " << c.y << ')';
}

std::ostream &operator<<(std::ostream &s, glm::ivec2 const &c) {
    return s << '(' << c.x << ", " << c.y << ')';
}

std::ostream &operator<<(std::ostream &s, glm::mat4 const &m) {
    for(int i = 0; i < 4; ++i) {
        s << glm::row(m, i);
        if(i != 3)
            s << '\n';
    }

    return s;
}

std::ostream &operator<<(std::ostream &s, glm::mat3 const &m) {
    for(int i = 0; i < 3; ++i) {
        s << glm::row(m, i);
        if(i != 2)
            s << '\n';
    }

    return s;
}

std::ostream &operator<<(std::ostream &s, glm::mat2 const &m) {
    for(int i = 0; i < 2; ++i) {
        s << glm::row(m, i);
        if(i != 1)
            s << '\n';
    }

    return s;
}
