//
//  CoreGL.hpp
//  CoreGL
//
//  Created by Rémi on 11/11/2015.
//  Copyright © 2015 Rémi. All rights reserved.
//

#ifndef CoreGL_hpp
#define CoreGL_hpp

#include <string>
#include <si-units/Units.h>
#include "EventManager.h"
#include "GLContext.h"
#include <memory>

namespace CoreGL {
    /**
     * Initializes the CoreGL library. Should be called before any operation is made on any other
     * component of this lib or any method of this namespace, except for the initialized() check.
     * @param context The bridge between this lib and the one used for windowing and the OpenGL
     * context creation.
     * @param eventManager The bridge between this lib and the one used for the events handling.
     * @param resourcesPath The filesystem path to the resources of this lib (shaders).
     */
    void init(std::unique_ptr<GLContext> context, std::unique_ptr<EventManager> eventManager, std::string resourcesPath);

    /**
     * Destroys every resource allocated by CoreGL, along with the GLContext and EventManager
     * provided at initialization time.
     * No method belonging to the CoreGL namespace may be called after this function returns, except
     * for the initialized method, which will return false then on.
     */
    void clean();

    /**
     * Checks whether the CoreGL library has been initialized through the init() call, and that the
     * clean() function was not called.
     * A value of true means that the lib is ready for use.
     */
    bool initialized();

    /**
     * The CoreGL internal resources path attributed at initialization.
     */
    std::string const &resourcesPath();

    /**
     * The time elapsed since the call to the iniit() method.
     */
    Units::Duration timeSinceInit();

    /**
     * Gives access to the event manager provided during initialization.
     */
    EventManager const &eventManager();
}

#endif /* CoreGL_hpp */
