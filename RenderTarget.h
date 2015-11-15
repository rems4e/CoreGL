//
//  RenderTarget.h
//  RPG 3D
//
//  Created by Rémi on 17/07/13.
//
//

#ifndef __RPG_3D__RenderTarget__
#define __RPG_3D__RenderTarget__

#include <stack>
#include "Geometry.h"
#include "GL.h"

class RenderTarget {
public:
    RenderTarget(ivec2 const &size);
    virtual ~RenderTarget();

    static RenderTarget &top();
    static void push(RenderTarget &f);
    // Ne pas supprimer plus qu'on n'a ajouté…
    static void pop();

    ivec2 const &size() const {
        return _size;
    }
    virtual void resize(ivec2 const size) {
        _size = size;
    }

    // Le rapport entre la dimension actuelle et 800*600, pour permettre un redimensionnement correct des éléments
    // d'interface
    vec2 scale();
    // std::min(scale().x, scale().y)
    float minScale();

    Rectangle const &viewport();
    void pushViewport(Rectangle const &, bool intersection = true);
    void popViewport();

    void pushTransformation(mat4 const &transfo);
    // Si on supprime plus que ce que l'on doit, exception lancée !
    void popTransformation() {
        this->popTransformations(1);
    }
    void popTransformations(int nbSupr);

    void setProjection(mat4 const &projection);

    mat4 const &projection();
    mat4 const &modelView();

    virtual GLuint identifier() const = 0;

    enum { VIEWPORT_BIT = 1 << 16, MODELVIEW_BIT = 1 << 17 };
    // TODO: bindAndClear();
    void clear(GLbitfield mask);

protected:
    void bind();
    void setViewport(Rectangle const &rect);

private:
    static std::stack<RenderTarget *> _renderTargets;

    ivec2 _size;

    std::stack<Rectangle> _viewports;

    std::stack<mat4> _modelView;
    mat4 _projection;
};

#endif /* defined(__RPG_3D__RenderTarget__) */
