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

namespace CoreGL {
    /**
     * The bridge between this lib and the library managing the user events.
     * Has to be inherited from by the users of CoreGL.
     */
    class EventManager {
    public:
        virtual ivec2 cursorPosition() const = 0;
    };
}

#endif /* EventManager_h */
