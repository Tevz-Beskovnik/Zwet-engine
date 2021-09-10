#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <scene.h>
#include <attributeLayout.h>
#include <drawer.h>

namespace ZWET
{
    class Renderer
    {
        public:
            Renderer(SharedPtr<Scene> scene);

            ~Renderer();

            void init();

            void viewport(size_t x, size_t y, size_t width, size_t height);

            static UniquePtr<Renderer> create(SharedPtr<Scene> scene);

            void frame();

        private:
            SharedPtr<Scene> scene;

            void stepStart(); // at vertex buffer bind 
            // ^ (optimal place to do framebuffer draw call)
            void step(); // at uniform bind

            void stepEnd(); // at draw call
    };
}