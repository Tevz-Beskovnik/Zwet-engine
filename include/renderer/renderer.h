#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <scene.h>
#include <attributeLayout.h>
#include <drawer.h>

namespace ZWET
{
    using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>;

    class Renderer
    {
        public:
            Renderer(SharedPtr<Scene>& scene);

            ~Renderer();

            void init();

            void viewport(size_t x, size_t y, size_t width, size_t height);

            static UniquePtr<Renderer> create(SharedPtr<Scene>& scene);

            void frame();

        private:
            SharedPtr<Scene>& scene;
            EntityMap& entities;
            SharedPtr<Camera>& camera;

            void create();
    };
}