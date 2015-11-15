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

class Screen : public RenderTarget {
public:
    Screen();
    ~Screen();

    GLuint identifier() const override {
        return 0;
    }
};

#endif
