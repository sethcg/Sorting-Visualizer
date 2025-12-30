#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <SDL3/SDL.h>

#include <Color.hpp>
#include <ListManager.hpp>
#include <Rect.hpp>

class Renderer {
    public:
        Renderer(SDL_Renderer* renderer) {
            this->renderer = renderer;
        };

        void DrawList(const std::vector<Rect::Rectangle>& items, ListManager& listManager);
        
        void DrawRect(const Rect::Rectangle& rect);

    private:
        SDL_Renderer* renderer;
};

#endif