//
//  Affichage.h
//  Projet2MIC
//
//  Created by Rémi on 12/08/12.
//  Copyright (c) 2012 Rémi Saurel. All rights reserved.
//

#ifndef EN_TETE_AFFICHAGE
#define EN_TETE_AFFICHAGE

#include "Geometry.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "GL.h"
#include "Screen.h"
#include "Framebuffer.h"
#include <si-units/Units.h>
#include "GLContext.h"

class Texture;

using ObserverID = unsigned long;

namespace ContextManager {
    bool hasGLContext();

    GLsizei maxSamples();
    GLfloat maxAnisotropy();

    void changeResolution(ivec2 const &resolution, bool fullScreen, bool vsync, GLsizei samples, GLfloat anisotropy);

    // Les résolutions disponibles pour la fenêtre/le plein écran.
    std::vector<ivec2> availableResolutions(bool fullScreen);

    ivec2 size();
    bool fullScreen();

    // Pointeur
    bool cursorVisible();
    void setCursorVisibility(bool visible);

    Texture const &cursor();
    void setCursor(Texture const &tex, ivec2 const &distanceToCross = {});
    void resetCursor();

    void addResolutionObserver(std::function<void()> const &f, ObserverID &observerID);
    void removeResolutionObserver(ObserverID const &observer);

    float ratio();
    Rectangle bounds();

    Units::Frequency averagRefreshRate();
    Units::Frequency instantRefreshRate();

    Texture currentDisplay();

    void flush();

    Texture &emptyTex();
}

#endif
