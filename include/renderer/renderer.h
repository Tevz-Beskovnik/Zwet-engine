#pragma once

#include <core.h>
#include <utils.h>

namespace ZWET
{
    struct AttirbuteLayout
    {

    };

    struct RendererSettings
    {

    };

    class Renderer
    {
        public:
            Renderer();

            ~Renderer();

            static UniquePtr<Renderer> create();

            void frame();

        private:
    };
}