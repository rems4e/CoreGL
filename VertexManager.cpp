//
//  VertexManager.cpp
//  CoreGL
//
//  Created by Rémi on 18/07/13.
//
//

#include "VertexManager.h"
#include <stack>
#include "Shader.h"
//#include "../data/shaders/attribLocation.h"
#include "GLBuffer.h"

#define VERT_COORDS_LOCATION 0
#define TEX_COORDS_LOCATION 1
#define COLOR_LOCATION 2
#define NORMAL_LOCATION 3
#define BITANGENT_LOCATION 4
#define TANGENT_LOCATION 5

namespace CoreGL {

    static constexpr size_t _buffersCount = 8;
    static constexpr size_t _bufferVertices = 3 * 400;

    vec4 const Color::black(0, 0, 0, 1);
    vec4 const Color::grey(0.5, 0.5, 0.5, 1);
    vec4 const Color::lightGrey(0.8, 0.8, 0.8, 1);
    vec4 const Color::darkGrey(0.3, 0.3, 0.3, 1);
    vec4 const Color::white(1, 1, 1, 1);
    vec4 const Color::red(1, 0, 0, 1);
    vec4 const Color::green(0, 1, 0, 1);
    vec4 const Color::blue(0, 0, 1, 1);
    vec4 const Color::yellow(1, 1, 0, 1);
    vec4 const Color::transparent(0, 0, 0, 0);

    vec4 Color::makeFromColor(vec4 const &vec, vec4::value_type alpha) {
        return vec4{vec.r, vec.g, vec.b, alpha};
    }

#define STATS

    namespace VertexManager {
        size_t const npos = static_cast<size_t>(-1);

        std::unique_ptr<VertexBuffer> _lineBuffer;
        std::unique_ptr<GLBufferedBuffer<GL_ARRAY_BUFFER>> _vbo[_buffersCount];
        int _currentBuffer = 0;
        // Not deleted, the GL context deletion will care of that for us
        std::unique_ptr<VertexArrayObject> _sharedVAO, _vao;

        size_t _nbSommets = 0;
        std::stack<vec4::value_type> _opacite;
        vec4 _teinte = Color::white;

        void init() {
            _lineBuffer = std::make_unique<VertexBuffer>(2 * (3 + 4) * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
            for(int i = 0; i < _buffersCount; ++i) {
                _vbo[i] = std::make_unique<GLBufferedBuffer<GL_ARRAY_BUFFER>>(
                static_cast<GLint>(_bufferVertices * (5 + 4) * sizeof(GLfloat)), nullptr, GL_STREAM_DRAW);
            }

            // Initialization of the VAO used by pushVertex
            _sharedVAO = std::make_unique<VertexArrayObject>();
            _vao = std::make_unique<VertexArrayObject>();

            _vao->beginEditing();
            _vao->enableVertexAttribArray(VERT_COORDS_LOCATION);
            _vao->enableVertexAttribArray(TEX_COORDS_LOCATION);
            _vao->enableVertexAttribArray(COLOR_LOCATION);
            _vao->endEditing();
        }
    }

#ifdef STAT
    static int nbVert = 0;
#endif

    VertexArrayObject &VertexManager::sharedVAO() {
        return *_sharedVAO;
    }

    void VertexManager::pushVertex(vec2 const &pos, vec2 const &posTex, vec4 const &couleur) {
        _vbo[_currentBuffer]->setData(vec3(pos.x, pos.y, 0),
                                      _nbSommets * (3 + 2 + 4) * sizeof(GLfloat),
                                      3 * sizeof(GLfloat));
        _vbo[_currentBuffer]->setData(posTex, (_nbSommets * (3 + 2 + 4) + 3) * sizeof(GLfloat), 2 * sizeof(GLfloat));
        _vbo[_currentBuffer]->setData(couleur,
                                      (_nbSommets * (3 + 2 + 4) + 3 + 2) * sizeof(GLfloat),
                                      4 * sizeof(GLfloat));

        ++_nbSommets;

        if(_nbSommets % 3 == 0 && _nbSommets == _bufferVertices) {
            VertexManager::flush();
            std::cerr << "VertexManager buffer may be too small!" << std::endl;
        }
#ifdef STAT
        ++nbVert;
#endif
    }

    void VertexManager::drawVertices(GLenum mode,
                                     size_t vertices,
                                     GLBufferTarget<GL_ARRAY_BUFFER> &buffer,
                                     size_t vertexPosition,
                                     size_t texturePosition,
                                     size_t colorPosition,
                                     size_t normalPosition,
                                     size_t stride) {
        _sharedVAO->beginEditing();
        buffer.bind();

        _sharedVAO->enableVertexAttribArray(VERT_COORDS_LOCATION);
        _sharedVAO->vertexAttribPointer(VERT_COORDS_LOCATION, 3, GL_FLOAT, GL_FALSE, GLsizei(stride), GLint(vertexPosition));

        if(texturePosition != npos) {
            _sharedVAO->enableVertexAttribArray(TEX_COORDS_LOCATION);
            _sharedVAO->vertexAttribPointer(TEX_COORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, GLsizei(stride), GLint(texturePosition));
        } else {
            _sharedVAO->vertexAttrib2f(COLOR_LOCATION, 0, 0);
        }
        if(colorPosition != npos) {
            _sharedVAO->enableVertexAttribArray(COLOR_LOCATION);
            _sharedVAO->vertexAttribPointer(COLOR_LOCATION, 4, GL_FLOAT, GL_TRUE, GLsizei(stride), GLint(colorPosition));
        } else {
            _sharedVAO->vertexAttrib4f(COLOR_LOCATION, 1, 1, 1, 1);
        }
        if(normalPosition != npos) {
            _sharedVAO->enableVertexAttribArray(NORMAL_LOCATION);
            _sharedVAO->vertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_TRUE, GLsizei(stride), GLint(normalPosition));
        } else {
            _sharedVAO->vertexAttrib3f(NORMAL_LOCATION, 0, 1, 0);
        }
        _sharedVAO->endEditing();

        glDrawArrays(mode, 0, static_cast<GLsizei>(vertices));

        _sharedVAO->beginEditing();
        _sharedVAO->disableVertexAttribArray(VERT_COORDS_LOCATION);
        if(texturePosition != npos)
            _sharedVAO->disableVertexAttribArray(TEX_COORDS_LOCATION);
        if(colorPosition != npos)
            _sharedVAO->disableVertexAttribArray(COLOR_LOCATION);
        if(normalPosition != npos)
            _sharedVAO->disableVertexAttribArray(NORMAL_LOCATION);

        _sharedVAO->endEditing();
    }

    void VertexManager::drawVertices(GLenum mode,
                                     size_t vertices,
                                     GLBufferTarget<GL_ARRAY_BUFFER> &buffer,
                                     size_t vertexPosition,
                                     size_t texturePosition,
                                     size_t colorPosition,
                                     size_t normalPosition,
                                     size_t stride,
                                     GLBufferTarget<GL_ELEMENT_ARRAY_BUFFER> &ibo,
                                     size_t indicesPosition) {
        _sharedVAO->beginEditing();
        buffer.bind();

        _sharedVAO->enableVertexAttribArray(VERT_COORDS_LOCATION);
        _sharedVAO->vertexAttribPointer(VERT_COORDS_LOCATION, 3, GL_FLOAT, GL_FALSE, GLsizei(stride), GLint(vertexPosition));

        if(texturePosition != npos) {
            _sharedVAO->enableVertexAttribArray(TEX_COORDS_LOCATION);
            _sharedVAO->vertexAttribPointer(TEX_COORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, GLsizei(stride), GLint(texturePosition));
        } else {
            _sharedVAO->vertexAttrib2f(COLOR_LOCATION, 0, 0);
        }
        if(colorPosition != npos) {
            _sharedVAO->enableVertexAttribArray(COLOR_LOCATION);
            _sharedVAO->vertexAttribPointer(COLOR_LOCATION, 4, GL_FLOAT, GL_TRUE, GLsizei(stride), GLint(colorPosition));
        } else {
            _sharedVAO->vertexAttrib4f(COLOR_LOCATION, 1, 1, 1, 1);
        }
        if(normalPosition != npos) {
            _sharedVAO->enableVertexAttribArray(NORMAL_LOCATION);
            _sharedVAO->vertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_TRUE, GLsizei(stride), GLint(normalPosition));
        } else {
            _sharedVAO->vertexAttrib3f(NORMAL_LOCATION, 0, 1, 0);
        }
        ibo.bind();

        _sharedVAO->endEditing();
        glDrawElements(mode, static_cast<GLsizei>(vertices), GL_UNSIGNED_INT, reinterpret_cast<void *>(indicesPosition));

        _sharedVAO->beginEditing();
        _sharedVAO->disableVertexAttribArray(VERT_COORDS_LOCATION);
        if(texturePosition != npos)
            _sharedVAO->disableVertexAttribArray(TEX_COORDS_LOCATION);
        if(colorPosition != npos)
            _sharedVAO->disableVertexAttribArray(COLOR_LOCATION);
        if(normalPosition != npos)
            _sharedVAO->disableVertexAttribArray(NORMAL_LOCATION);

        _sharedVAO->endEditing();
    }

    void VertexManager::flush() {
        if(_nbSommets) {
            _vao->beginEditing();
            _vbo[_currentBuffer]->update();

            _vao->vertexAttribPointer(VERT_COORDS_LOCATION, 3, GL_FLOAT, GL_FALSE, (3 + 2 + 4) * sizeof(GLfloat), 0);
            _vao->vertexAttribPointer(
            TEX_COORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, (3 + 2 + 4) * sizeof(GLfloat), 3 * sizeof(GLfloat));
            _vao->vertexAttribPointer(
            COLOR_LOCATION, 4, GL_FLOAT, GL_TRUE, (3 + 2 + 4) * sizeof(GLfloat), (3 + 2) * sizeof(GLfloat));
            _vao->endEditing();

            _vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_nbSommets));

            _currentBuffer = (_currentBuffer + 1) % _buffersCount;

            _nbSommets = 0;
        }
    }

    vec4::value_type VertexManager::alpha() {
        if(_opacite.empty())
            return 1.0;
        return _opacite.top();
    }

    vec4 const &VertexManager::hue() {
        return _teinte;
    }

    void VertexManager::setHue(const vec4 &c) {
        _teinte = c;
    }

    void VertexManager::pushAlpha(vec4::value_type o) {
        _opacite.push(o * VertexManager::alpha());
    }

    void VertexManager::popAlpha() {
        _opacite.pop();
    }

    void VertexManager::pushTex(Texture const &tex, vec2 const &position, bool upsideDown) {
        VertexManager::pushTex(tex, position, Rectangle{vec2{}, tex.size()}, upsideDown);
    }

    void VertexManager::pushTex(Texture const &tex, vec2 const &position, Rectangle scissors, bool upsideDown) {
        Rectangle vert(position, vec2(scissors.size()));

        if(upsideDown) {
            scissors.top = scissors.top + scissors.height;
            scissors.height = -scissors.height;
        }

        ShaderProgram::current().setTexture("_tex", tex);

        vec4 const &teinte = VertexManager::hue();
        vec4 c(1 - teinte.a * (1 - teinte.r),
               1 - teinte.a * (1 - teinte.g),
               1 - teinte.a * (1 - teinte.b),
               VertexManager::alpha());
        ivec2 const &dim = tex.size();

        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left, vert.top)),
                                  vec2(scissors.left / dim.x, scissors.top / dim.y),
                                  c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left, vert.top + vert.height)),
                                  vec2(scissors.left / dim.x, (scissors.top + scissors.height) / dim.y),
                                  c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left + vert.width, vert.top)),
                                  vec2((scissors.left + scissors.width) / dim.x, scissors.top / dim.y),
                                  c);

        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left, vert.top + vert.height)),
                                  vec2(scissors.left / dim.x, (scissors.top + scissors.height) / dim.y),
                                  c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left + vert.width, vert.top + vert.height)),
                                  vec2((scissors.left + scissors.width) / dim.x,
                                       (scissors.top + scissors.height) / dim.y),
                                  c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(vec2(vert.left + vert.width, vert.top)),
                                  vec2((scissors.left + scissors.width) / dim.x, scissors.top / dim.y),
                                  c);
    }

    void VertexManager::pushRect(Rectangle const &r, vec4 const &c) {
        VertexManager::pushQuad(vec2(r.left, r.top),
                                vec2(r.left, r.top + r.height),
                                vec2(r.left + r.width, r.top + r.height),
                                vec2(r.left + r.width, r.top),
                                c);
    }

    void VertexManager::pushLine(vec2 const &depart, vec2 const &arrivee, vec4 const &c, dimension_t epaisseur) {
        if(Geometry::nullVector(depart - arrivee))
            return;
        vec2 normale = glm::normalize(depart - arrivee) * epaisseur;
        std::swap(normale.x, normale.y);
        normale.y *= -1;

        VertexManager::pushQuad(depart - normale, depart + normale, arrivee + normale, arrivee - normale, c);
    }

    void VertexManager::pushQuad(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec2 const &p4, vec4 const &c) {
        ShaderProgram::current().setTexture("_tex", ContextManager::emptyTex());

        VertexManager::pushVertex(VertexManager::pixelToScreen(p1), vec2(0, 0), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p2), vec2(1, 0), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p4), vec2(0, 1), c);

        VertexManager::pushVertex(VertexManager::pixelToScreen(p4), vec2(0, 1), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p2), vec2(1, 0), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p3), vec2(1, 1), c);
    }

    void VertexManager::pushTriangle(vec2 const &p1, vec2 const &p2, vec2 const &p3, vec4 const &c) {
        ShaderProgram::current().setTexture("_tex", ContextManager::emptyTex());

        VertexManager::pushVertex(VertexManager::pixelToScreen(p1), vec2(0, 0), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p2), vec2(1, 0), c);
        VertexManager::pushVertex(VertexManager::pixelToScreen(p3), vec2(1, 1), c);
    }

    vec2 VertexManager::pixelToScreen(vec2 vec) {
        vec.x = (vec.x / RenderTarget::top().viewport().width * 2 - 1);
        vec.y = -(vec.y / RenderTarget::top().viewport().height * 2 - 1);
        return vec;
    }

    Rectangle VertexManager::pixelToScreen(Rectangle const &r) {
        return Rectangle(VertexManager::pixelToScreen(r.origin()),
                         vec2(r.width / ContextManager::size().x, r.height / ContextManager::size().y));
    }
}
