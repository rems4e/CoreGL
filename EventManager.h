//
//  EventManager.h
//  CoreGL
//
//  Created by Rémi on 11/11/2015.
//  Copyright © 2015 Rémi. All rights reserved.
//

#ifndef EventManager_h
#define EventManager_h

#include "Geometry.h"

class EventManager {
public:
    virtual ivec2 cursorPosition() const = 0;
};

#endif /* EventManager_h */
