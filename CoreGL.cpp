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

namespace CoreGL {
    namespace {
        std::unique_ptr<EventManager> _eventManager;
        std::string _resourcesPath;
        TimePoint _initTime;
        std::atomic_bool _initialized{false};
    }

    namespace ContextManager {
        void init(std::unique_ptr<GLContext> context);
        void clean();
    }

    void init(std::unique_ptr<GLContext> context, std::unique_ptr<EventManager> eventManager, std::string resourcesPath) {
        _eventManager = std::move(eventManager);
        _resourcesPath = std::move(resourcesPath);
        _initTime = TimePoint::now();

        ContextManager::init(std::move(context));

        _initialized = true;
    }

    void clean() {
        _initialized = false;
        ContextManager::clean();
    }

    bool initialized() {
        return _initialized;
    }

    std::string const &resourcesPath() {
        return _resourcesPath;
    }

    Units::Duration timeSinceInit() {
        return TimePoint::now() - _initTime;
    }

    EventManager const &eventManager() {
        return *_eventManager;
    }
}
