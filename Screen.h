//
//  Screen.h
//  RPG 3D
//
//  Created by Rémi on 18/07/13.
//
//

#ifndef SCREEN_H
#define SCREEN_H

#include "RenderTarget.h"
#include "ContextManager.h"

namespace CoreGL {

    class Screen : public RenderTarget {
    public:
        Screen()
                : RenderTarget(ContextManager::size()) {}
        ~Screen() = default;

        GLuint identifier() const override {
            return 0;
        }
    };
}

#endif
