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

class GLContext {
public:
    GLContext() = default;
    virtual ~GLContext() = default;

    virtual std::vector<ivec2> availableResolutions(bool fullScreen) = 0;

    virtual void init() = 0;
    virtual void changeResolution(ivec2 const &resolution, bool fullScreen, bool vsync) = 0;

    virtual bool vsync() const = 0;
    virtual bool fullScreen() const = 0;
    virtual ivec2 size() const = 0;

    virtual GLsizei samples() const = 0;
    virtual void setSamples(GLsizei samples) = 0;

    virtual GLfloat anisotropy() const = 0;
    virtual void setAnisotropy(GLfloat anisotropy) = 0;

    virtual void swapBuffers() = 0;
    virtual void showWindow() = 0;
};

#endif /* GLContext_h */
