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
     * component of this lib or any method of this namespace.
     * @param context The bridge between this lib and the one used for windowing and the OpenGL
     * context creation.
     * @param eventManager The bridge between this lib and the one used for the events handling.
     * @param resourcesPath The filesystem path to the resources of this lib (shaders).
     */
    void init(std::unique_ptr<GLContext> context, std::unique_ptr<EventManager> eventManager, std::string resourcesPath);
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
