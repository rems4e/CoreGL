//
//  Geometrie.h
//  Projet2MIC
//
//  Créé par Marc Promé et Rémi Saurel.
//  Ce fichier et son contenu sont librement distribuables, modifiables et utilisables pour toute
//  œuvre non commerciale,
//  à condition d'en citer les auteurs.
//

#ifndef EN_TETE_Geometrie
#define EN_TETE_Geometrie

#include <iosfwd>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <type_traits>

namespace CoreGL {
    using ::glm::ivec2;
    using ::glm::vec2;
    using ::glm::vec3;
    using ::glm::vec4;
    using ::glm::mat2;
    using ::glm::mat3;
    using ::glm::mat4;

    typedef vec3::value_type coordinate_t;
    typedef coordinate_t dimension_t;

    namespace Geometry {
        inline bool nullValue(coordinate_t v) {
            return (v < 0 ? -v : v) < 0.00001f;
        }

        template <typename Vec>
        inline bool nullVector(Vec const &v) {
            for(int i = 0; i < v.length(); ++i)
                if(!nullValue(v[i]))
                    return false;
            return true;
        }

        template <typename Vec>
        inline Vec orthogonalProjection(Vec const &vec, Vec const &projectionDirection) {
            vec3 const v = glm::normalize(projectionDirection);
            return projectionDirection * glm::dot(vec, v);
        }

        inline vec3 sphericToCartesian(vec3 const &coord) {
            using float_t = vec3::value_type;
            float_t const rho = coord.x;
            float_t const theta = (coord.y + 90) / 180 * M_PI;
            float_t const phi = coord.z / 180 * M_PI;

            float_t const sinTheta = std::sin(theta);
            float_t const cosTheta = std::cos(theta);
            float_t const cosPhi = std::cos(phi);
            float_t const sinPhi = std::sin(phi);

            return vec3(sinTheta * cosPhi, cosTheta, sinTheta * sinPhi) * rho;
        }

        // Transformations
        mat4 perspective(float angle, float ratio, float near, float far);
        mat4 translate(vec3 const &vec);
        mat4 scale(vec3 const &vec);
        mat4 rotate(float angle, vec3 vec); // angle in degrees

        // Camera
        mat4 camera(vec3 const &position, vec3 const &target, vec3 const &up);
        mat4 cameraSphere(vec3 const &relativeToSphere, vec3 const &target, vec3 const &up);
    }

    // Autoriser la multiplication/division entre un vecteur glm et autre chose qu'un float
    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec2<T>>
    operator/(glm::tvec2<T> v, Number const &nb) {
        v /= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec3<T>>
    operator/(glm::tvec3<T> v, Number const &nb) {
        v /= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec4<T>>
    operator/(glm::tvec4<T> v, Number const &nb) {
        v /= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec2<T>>
    operator*(glm::tvec2<T> v, Number const &nb) {
        v *= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec3<T>>
    operator*(glm::tvec3<T> v, Number const &nb) {
        v *= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value, glm::tvec4<T>>
    operator*(glm::tvec4<T> v, Number const &nb) {
        v *= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec2<T>>
    operator*(Number const &nb, glm::tvec2<T> v) {
        v *= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec3<T>>
    operator*(Number const &nb, glm::tvec3<T> v) {
        v *= nb;
        return v;
    }

    template <typename T, typename Number>
    inline std::enable_if_t<std::is_arithmetic<Number>::value && !std::is_same<T, Number>::value, glm::tvec4<T>>
    operator*(Number const &nb, glm::tvec4<T> v) {
        v *= nb;
        return v;
    }
}

// Affichage des vecteurs/matrices
std::ostream &operator<<(std::ostream &s, glm::vec4 const &c);
std::ostream &operator<<(std::ostream &s, glm::vec3 const &c);
std::ostream &operator<<(std::ostream &s, glm::vec2 const &c);
std::ostream &operator<<(std::ostream &s, glm::ivec2 const &c);
std::ostream &operator<<(std::ostream &s, glm::mat4 const &m);
std::ostream &operator<<(std::ostream &s, glm::mat3 const &m);
std::ostream &operator<<(std::ostream &s, glm::mat2 const &m);

#include "Rectangle.h"

#endif
