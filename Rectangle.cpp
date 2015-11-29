//
//  Rectangle.cpp
//  CoreGL
//
//  Created by Rémi on 28/07/11.
//  Additional contributor (2012): Marc Promé
//

#include "Rectangle.h"
#include <iostream>

namespace CoreGL {
    std::ostream &operator<<(std::ostream &s, Rectangle const &r) {
        return s << "{(" << r.left << ", " << r.top << "), (" << r.width << ", " << r.height
                 << ")}";
    }
}
