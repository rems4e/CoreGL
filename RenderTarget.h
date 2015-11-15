//
//  RenderTarget.h
//  RPG 3D
//
//  Created by Rémi on 17/07/13.
//
//

#ifndef __RPG_3D__RenderTarget__
#define __RPG_3D__RenderTarget__

#include <stack>
#include "Geometry.h"
#include "GL.h"

namespace CoreGL {

    /**
     * A generic class that can be set as a target for OpenGL rendering.
     */
    class RenderTarget {
    public:
        RenderTarget(ivec2 const &size);
        virtual ~RenderTarget();

        /**
         * The currently active RenderTarget, which will be rendered to by drawing commands.
         */
        static RenderTarget &top();

        /**
         * Changes the currently active RenderTarget. It may be pop()ed later, returning in the same
         * state as before this call.
         */
        static void push(RenderTarget &f);

        /**
         * Sets the currently active RenderTarget to the one before the last push() call.
         * Be careful not to pop too much!
         */
        static void pop();

        /**
         * The size in pixels of the target.
         */
        ivec2 const &size() const {
            return _size;
        }

        /**
         * Change the size of the target. The new size is specified in pixels.
         */
        virtual void resize(ivec2 const size) {
            _size = size;
        }

        /**
         * Utility function that returns the vector {size().x / 800.0, size().y / 600.0}. Can be
         * used to scale GUI elements or for any purpose you envision.
         */
        vec2 scale();

        /**
         * Returns the result of std::min(scale().x, scale().y).
         */
        vec2::value_type minScale();

        /**
         * Returns the current rectangle in which rendering is allowed. Any rendering outside of
         * this rectangle is discarded, and only parts of overlapping renderings that are inside the
         * rectangle will be kept.
         */
        Rectangle const &viewport();

        /**
         * Restricts the current viewport with the provided rectangle, according to the intersection
         * argument in the following way:
         * If intersection is true, then the new viewport is equal to param.intersection(viewport())
         * Else, the new viewport is set to the parameter itself.
         * The previous viewports may be retrieved by appropriate calls to popViewPort().
         */
        void pushViewport(Rectangle const &, bool intersection = true);

        /**
         * Retrives the viewport in place before the last call to pushViewport().
         * Be careful not to pop too many times!
         */
        void popViewport();

        /**
         * Applies the specified transformation matrix to the transformations previously in place.
         *
         * Each call to this method involves the copy of a 4×4 matrix uniform in the currently
         * active shader. To avoid unecessary overhead when applying multiple transformations at
         * once, compute the composed transformation first, and then pass the result to this
         * function.
         */
        void pushTransformation(mat4 const &transfo);

        /**
         * Retrives the transformation state in place before the last call to pushTransformation().
         * Be careful not to pop too many times!
         *
         * Each call to this method involves the copy of a 4×4 matrix uniform in the currently
         * active shader. To avoid unecessary overhead when popping multiple transformations at
         * once, call the parametrized overload of this method to pop them all with only one shader
         * uniform update.
         */
        void popTransformation() {
            this->popTransformations(1);
        }
        /**
         * Retrives the transformation state in place before the last count calls to
         * pushTransformation().
         * Be careful not to pop too many times!
         *
         * Applies only one uniform copy to the currently active shader, even if count > 1.
         */
        void popTransformations(int count);

        /**
         * Sets the projection matric for the render target.
         */
        void setProjection(mat4 const &projection);

        /**
         * Returns the projection matrix currently in place for the render target.
         */
        mat4 const &projection();

        /**
         * Returns the transformation matrix currently in place for the render target.
         */
        mat4 const &modelView();

        /**
         * The OpenGL identifier for the RenderTarget.
         */
        virtual GLuint identifier() const = 0;

        enum { VIEWPORT_BIT = 1 << 16, MODELVIEW_BIT = 1 << 17 };
        // TODO: bindAndClear();
        /**
         * This function is used to clear the render target. The parameter is a mask of different
         * binary values, found in the enum above as well as in the values
         * {GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT}.
         */
        void clear(GLbitfield mask);

    protected:
        void bind();
        void setViewport(Rectangle const &rect);

    private:
        static std::stack<RenderTarget *> _renderTargets;

        ivec2 _size;

        std::stack<Rectangle> _viewports;

        std::stack<mat4> _modelView;
        mat4 _projection;
    };
}

#endif /* defined(__RPG_3D__RenderTarget__) */
