//
//  ContextManager.h
//  CoreGL
//
//  Created by Rémi on 12/08/12.
//

#ifndef COREGL_CONTEXT_MANAGER_H
#define COREGL_CONTEXT_MANAGER_H

#include "Geometry.h"
#include <string>
#include <vector>
#include "GL.h"
#include "Framebuffer.h"
#include <si-units/Units.h>
#include "GLContext.h"

namespace CoreGL {

    class Texture;

    /**
     * A class that allows to set observers of the context's resolution changes.
     * The observer function will be called when a resolution change occurs, for the life span of
     * the
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
         * The moved-from object will not participate in any future resolution change notification
         * and
         * can be safely destroyed.
         * The moved-to or new object will manage notifications to the underlying function until it
         * is
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
         * Notifies the underlying GLContext that it needs to change its resolution.
         * The GLContext is responsible for actually modifying the resolution.
         */
        void updateResolution();

        /**
         * Returns a list of the screen resolutions the underlying context is able to provide, in
         * fullscreen or windowed mode.
         * @param fullscreen Whether the requested resolutions are for fullscreen mode or not.
         */
        std::vector<ivec2> availableResolutions(bool fullScreen);

        /**
         * The size of the context in pixels, i.e. the size of the drawable area.
         */
        ivec2 size();
        /**
         * Returns true if the current context is in fullscreen mode.
         */
        bool fullScreen();

        /**
         * Gets/sets the visibility of the mouse pointer.
         */
        bool pointerVisible();
        void setPointerVisibility(bool visible);

        /**
         * Sets the texture representing the mouse pointer. By default, there are not texture,
         * meaning
         * that no pointer will be shown, regardless of its visibility set above.
         */
        Texture const &pointer();
        /**
         * @param tex The new image that will be used as the mouse pointer.
         * @param distanceToHotSpot The shift from the origin of the image to the desired hotspot of
         * the
         * pointer.
         */
        void setPointer(Texture const &tex, ivec2 const &distanceToHotspot = {});
        /**
         * Resets the default mouse pointer, i.e. no image at all.
         */
        void resetPointer();

        /**
         * The width-to-height ratio of the current display (a 1024×768 context will have a 1.25
         * ratio).
         */
        float ratio();
        /**
         * A rectangle with zero-origin and the same size as returned by the size() function.
         */
        Rectangle bounds();

        /**
         * The context's refresh rate, averaged on a 3 seconds period. This provides a stable
         * indicator
         * of the refresh rate.
         */
        Units::Frequency averagRefreshRate();

        /**
         * The instant refresh rate of the context, useful for in-game lag detection or movement
         * adaptation.
         */
        Units::Frequency instantRefreshRate();

        /**
         * Creates a new texture containing the image currently displayed on the back buffer. The
         * resulting image obviously depends on the current position in the rendering process.
         * The texels are fetched and copied from the video memory, which is a costly operation and
         * should not be abused.
         */
        Texture currentDisplay();

        /**
         * Flushes the current rendering pipeline and swaps the back buffer with the front buffer.
         */
        void flush();

        /**
         * An invisible (transparent), 1×1 sized texture, for what it's worth.
         */
        Texture const &emptyTex();
    }
}

#endif
