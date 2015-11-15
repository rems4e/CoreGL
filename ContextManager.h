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
#include "GL.h"
#include "Framebuffer.h"
#include <si-units/Units.h>
#include "GLContext.h"

class Texture;

/**
 * A class that allows to set observers of the context's resolution changes.
 * The observer function will be called when a resolution change occurs, for the life span of the
 * ResolutionObserverRAII object.
 */
class ResolutionObserverRAII {
public:
    /**
     * Created an observer that will be in charge of managing notifications to the given funtion
     * until the object is destroyed or moved from.
     * @param f The function that will be called when the context's resolution changes.
     */
    ResolutionObserverRAII(std::function<void()> f);
    template <typename Callable>
    ResolutionObserverRAII(Callable &&c)
            : ResolutionObserverRAII{std::function<void()>{c}} {}

    /**
     * Upon destruction, the object deinstalls the observer.
     */
    ~ResolutionObserverRAII();

    /**
     * Copy and affectations are discarded for this type, but move operations are allowed.
     * The moved-from object will not participate in any future resolution change notification and
     * can be safely destroyed.
     * The moved-to or new object will manage notifications to the underlying function until it is
     * destroyed or moved from.
     */
    ResolutionObserverRAII(ResolutionObserverRAII &&);
    ResolutionObserverRAII &operator=(ResolutionObserverRAII &&);

    /**
     * This method servers invokes the underlying observer function.
     * When the the observer function is null, this is a no-op.
     */
    void notify();

private:
    std::function<void()> _observerFun;
    std::uint64_t _id;
};

namespace ContextManager {
    /**
     * Checks whether the OpenGL context is in place or not. May be useful when creating/destroying
     * global variables whose initialization order is unspecified (in different translation units).
     */
    bool hasGLContext();

    /**
     * Context/implementation/driver specific values reflecting respectively the maximum multisample
     * value available, and the maximum texture filtering level available.
     */
    GLsizei maxSamples();
    GLfloat maxAnisotropy();

    void updateResolution();

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

    float ratio();
    Rectangle bounds();

    Units::Frequency averagRefreshRate();
    Units::Frequency instantRefreshRate();

    Texture currentDisplay();

    void flush();

    Texture &emptyTex();
}

#endif
