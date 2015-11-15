//
//  Screen.cpp
//  RPG 3D
//
//  Created by Rémi on 18/07/13.
//
//

#include "Screen.h"
#include "GL.h"
#include "ContextManager.h"

Screen::Screen() : RenderTarget(ContextManager::size()) {}

Screen::~Screen() {}
