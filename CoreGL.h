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
    void init(std::unique_ptr<GLContext> context, std::unique_ptr<EventManager> eventManager, std::string resourcesPath);
    std::string const &resourcesPath();

    Units::Duration timeSinceInit();

    EventManager const &eventManager();
}

#endif /* CoreGL_hpp */
