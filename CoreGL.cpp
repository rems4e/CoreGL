//
//  CoreGL.cpp
//  CoreGL
//
//  Created by Rémi on 11/11/2015.
//  Copyright © 2015 Rémi. All rights reserved.
//

#include "CoreGL.h"
#include <si-units/TimePoint.h>

using namespace Units;

namespace {
    std::unique_ptr<EventManager> _eventManager;
    std::string _resourcesPath;
    TimePoint _initTime;
}

namespace ContextManager {
    void init(std::unique_ptr<GLContext> context);
}

void CoreGL::init(std::unique_ptr<GLContext> context, std::unique_ptr<EventManager> eventManager, std::string resourcesPath) {
    _eventManager = std::move(eventManager);
    _resourcesPath = std::move(resourcesPath);
    _initTime = TimePoint::now();

    ContextManager::init(std::move(context));
}

std::string const &CoreGL::resourcesPath() {
    return _resourcesPath;
}

Units::Duration CoreGL::timeSinceInit() {
    return TimePoint::now() - _initTime;
}

EventManager const &CoreGL::eventManager() {
    return *_eventManager;
}
