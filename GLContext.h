//
//  GLContext.h
//  CoreGL
//
//  Created by Rémi on 10/11/2015.
//  Copyright © 2015 Rémi. All rights reserved.
//

#ifndef GLContext_h
#define GLContext_h

#include "GL.h"
#include "Geometry.h"
#include <vector>

namespace CoreGL {

    /**
     * The bridge between this lib and the library managing windowing and OpenGL context creation.
     * Has to be inherited from by the users of CoreGL.
     */
    class GLContext {
    public:
        GLContext() = default;
        virtual ~GLContext() = default;

        /**
         * Returns a list of the screen resolutions the context is able to provide, in
         * fullscreen or windowed mode.
         * @param fullscreen Whether the requested resolutions are for fullscreen mode or not.
         */
        virtual std::vector<ivec2> availableResolutions(bool fullScreen) = 0;

        /**
         * Actual initialization of the context. The implementation of this class is free to make
         * this call a no-op, as the context may be already initialized in the constructor of the
         * object.
         * However, overriding this methods allows the CoreGL::init() method itself to signal any
         * exception thrown here to the user.
         */
        virtual void init() = 0;

        /**
         * This methods is in charge of resizing the OpenGL context.
         */
        virtual void updateResolution() = 0;

        /**
         * This methods is in charge of checking if the context has been created in fullscreen mode.
         */
        virtual bool fullScreen() const = 0;

        /**
         * This methods is in charge of returning the size in pixels the context has been created
         * with.
         */
        virtual ivec2 size() const = 0;

        /**
         * This methods is in charge of swapping the front buffer with the back buffer.
         */
        virtual void swapBuffers() = 0;

        /**
         * This methods is in charge of displaying the window containing the OpenGL context. This
         * may be a no-op if the window is always onscreen.
         */
        virtual void showWindow() = 0;
    };
}

#endif /* GLContext_h */
