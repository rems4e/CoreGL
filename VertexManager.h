//
//  VertexManager.h
//  RPG 3D
//
//  Created by Rémi on 18/07/13.
//
//

#ifndef __RPG_3D__VertexManager__
#define __RPG_3D__VertexManager__

#include "Framebuffer.h"
#include "Geometry.h"
#include "GL.h"
#include "VertexArrayObject.h"
#include "GLBuffer.h"

namespace CoreGL {

    namespace Couleur {
        extern vec4 const noir, gris, grisClair, grisFonce, blanc, rouge, vert, bleu, jaune, transparent;

        vec4 makeFromCouleur(vec4 const &vec, vec4::value_type alpha);
    }

    namespace VertexManager {
        // Opacité de l'affichage de 0 = transparent à 255 = opaque.
        vec4::value_type alpha();
        void pushAlpha(vec4::value_type o);
        void popAlpha();

        // Teinte de l'image : Couleur::blanc -> image non teintée.
        vec4 const &hue();
        void setHue(vec4 const &c);

        void pushVertex(vec2 const &pos, vec2 const &posTex, vec4 const &couleur);

        vec2 pixelToScreen(vec2 vec);
        Rectangle pixelToScreen(Rectangle const &r);

        VertexArrayObject &sharedVAO();

        extern size_t const npos;

        void drawVertices(GLenum mode,
                          size_t vertices,
                          GLBufferTarget<GL_ARRAY_BUFFER> &buffer,
                          size_t vertexPosition,
                          size_t texturePosition,
                          size_t colorPosition,
                          size_t normalPosition,
                          size_t stride);
        void drawVertices(GLenum mode,
                          size_t vertices,
                          GLBufferTarget<GL_ARRAY_BUFFER> &buffer,
                          size_t vertexPosition,
                          size_t texturePosition,
                          size_t colorPosition,
                          size_t normalPosition,
                          size_t stride,
                          GLBufferTarget<GL_ELEMENT_ARRAY_BUFFER> &ibo,
                          size_t indicesPosition = 0);

        void pushLine(vec3 const &depart, vec3 const &arrivee, vec4 const &c);

        void pushTex(Texture const &tex, vec2 const &position, bool upsideDown = false);
        void pushTex(Texture const &tex, vec2 const &position, Rectangle scissors, bool upsideDown = false);

        // Affiche une couleur unie dans un rectangle.
        void pushRect(Rectangle const &r, vec4 const &c);
        void pushLine(vec2 const &depart, vec2 const &arrivee, vec4 const &c, dimension_t epaisseur = 1.0);
        void pushQuad(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec2 const &p4, vec4 const &c);
        void pushTriangle(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec4 const &c);

        void flush();
    }
}

#endif /* defined(__RPG_3D__VertexManager__) */
