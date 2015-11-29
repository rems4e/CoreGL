//
//  EventManager.h
//  CoreGL
//
//  Created by Rémi on 11/11/2015.
//

#ifndef COREGL_EVENT_MANAGER_H
#define COREGL_EVENT_MANAGER_H

#include "Geometry.h"

namespace CoreGL {
    /**
     * The bridge between this lib and the library managing the user events.
     * Has to be inherited from by the users of CoreGL.
     */
    class EventManager {
    public:
        /**
         * The position in pixel of the mouse pointer.
         */
        virtual ivec2 mousePosition() const = 0;
    };
}

#endif /* EventManager_h */
