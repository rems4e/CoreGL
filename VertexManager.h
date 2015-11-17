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

    /**
     * Some predefined color constants. A canonical color vector has all of its components in the
     * closed range [0, 1].
     */
    namespace Color {
        extern vec4 const black, grey, lightGrey, darkGrey, white, red, green, blue, yellow, transparent;

        /**
         * Copies the RGB value of the first parameter, and assigns the second parameter as the
         * alpha channel component's value.
         */
        vec4 makeFromColor(vec4 const &col, vec4::value_type alpha);
    }

    namespace VertexManager {
        //
        // Beginning of the drawing commands that share the same buffers.
        //
        // The following drawing commands are specifically meant to be used with a relatively small
        // number of vertices.
        // They are N-buffered, N being the count of vertex buffers that are being automatically
        // swapped between each other when the previous is full and has to be sent for actual
        // rendering.
        // All of these commands are in no mean meant to be used for 3D rendering, but rather for 2D
        // GUI display. That's why all the coordinates that are taken as parameters are expressed in
        // pixels in the window space, and why they would be so slow for massive vertices rendering.
        //
        // The last 2 commands require the user to provide its own vertex buffer, so they are not
        // involved in this process.
        //

        /**
         * Displays a colored rectangle on the current render target.
         */
        void pushRect(Rectangle const &r, vec4 const &color);
        void pushQuad(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec2 const &p4, vec4 const &color);

        /**
         * Displays a line of the specified width (in pixels) and color between the 2 given points.
         */
        void pushLine(vec2 const &start, vec2 const &end, vec4 const &color, vec4::value_type lineWidth = 1);

        /**
         * Draws a triangle of the specified color.
         */
        void pushTriangle(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec4 const &color);


        /**
         * Adds a single vertex, part of a triangle chain. Beware not to issue incomplete triangles!
         */
        void pushVertex(vec2 const &pos, vec2 const &posTex, vec4 const &color);

        /**
         * Forces a rendering of the shared vertex buffer.
         */
        void flush();

        /**
         * The alpha value here designates the transparency of the tex
         */
        vec4::value_type alpha();
        void pushAlpha(vec4::value_type o);
        void popAlpha();

        // Teinte de l'image : Color::white -> image non teintée.
        vec4 const &hue();
        void setHue(vec4 const &c);
        void pushTex(Texture const &tex, vec2 const &position, bool upsideDown = false);
        void pushTex(Texture const &tex, vec2 const &position, Rectangle scissors, bool upsideDown = false);


        //
        //
        //
        // End of the drawing commands that share the same buffers.
        //
        //
        //

        /**
         * Translates the parameter from the window space (ContextManager::size() in extents, {0, 0}
         * as origin) to the GL space (both coordinates have a range of [-1, 1] and {0, 0} represent
         * the center of the window.
         */
        vec2 pixelToScreen(vec2 vec);

        /**
         * Same as above, but translates the 4 corners of rectangle.
         */
        Rectangle pixelToScreen(Rectangle const &r);

        /**
         * The VAO used by all the drawing commands of this file.
         */
        VertexArrayObject &sharedVAO();

        /**
         * This constant may be specified as one of the *Position parameters of the functions below.
         * Passing this value means that the specified component is disbled.
         */
        extern size_t const npos;

        /**
         * Draws the vertices contained in the given buffer, with the given component's offsets.
         * All the components have to be interleaved, meaning that a buffer containing coordinates,
         * texture and color will have the following layout:
         * X1Y1Z1 U1V1/S1T1 R1G1B1A1 X2Y2Z2 U2V2/S2T2 R2G2B2A2
         * @param vertices The number of vertices to draw.
         * @param buffer The buffer containing the vertices' data.
         * @param vertexPosition The mandatory vertices coordinates. 3 coordinates per vertex.
         * @param texturePosition The optional texture coordinates. 2 coordinates per vertex. Pass
         * VertexManager::npos to disable these.
         * @param texturePosition The optional vertex color. 4 coordinates per vertex, normalized.
         * Pass VertexManager::npos to disable these.
         * @param normalPosition The optional vertex normal. 3 coordinates per vertex, normalized.
         * Pass VertexManager::npos to disable these.
         * @param stride The distance in bytes between 2 vertices' component, i.e. between X1 and X2
         * (following the layout given as example above).
         */
        void drawVertices(GLenum mode,
                          size_t vertices,
                          GLBufferTarget<GL_ARRAY_BUFFER> &buffer,
                          size_t vertexPosition,
                          size_t texturePosition,
                          size_t colorPosition,
                          size_t normalPosition,
                          size_t stride);


        /**
         * Draws the indexed vertices contained in the given buffer, indexed by the ibo buffer, and
         * with the given component's offsets.
         * All the components have to be interleaved, meaning that a buffer containing coordinates,
         * texture and color will have the following layout:
         * X1Y1Z1 U1V1/S1T1 R1G1B1A1 X2Y2Z2 U2V2/S2T2 R2G2B2A2
         * @param vertices The number of vertices to draw.
         * @param buffer The buffer containing the vertices' data.
         * @param vertexPosition The mandatory vertices coordinates. 3 coordinates per vertex.
         * @param texturePosition The optional texture coordinates. 2 coordinates per vertex. Pass
         * VertexManager::npos to disable these.
         * @param texturePosition The optional vertex color. 4 coordinates per vertex, normalized.
         * Pass VertexManager::npos to disable these.
         * @param normalPosition The optional vertex normal. 3 coordinates per vertex, normalized.
         * Pass VertexManager::npos to disable these.
         * @param stride The distance in bytes between 2 vertices' component, i.e. between X1 and X2
         * (following the layout given as example above).
         * @param ibo The index buffer object indexing the vertices in the GL_ARRAY_BUFFER.
         * @param indicesPosition The index of the byte where the relevant index are being stored in
         * the index buffer.
         */
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
    }
}

#endif /* defined(__RPG_3D__VertexManager__) */
