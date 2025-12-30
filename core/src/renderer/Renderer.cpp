#include <vector>

#include <SDL3/SDL.h>

#include <Color.hpp>
#include <ListManager.hpp>
#include <Rect.hpp>
#include <Renderer.hpp>

void Renderer::DrawList(const std::vector<Rect::Rectangle>& items, ListManager& listManager) {
    // RESIZE LIST RECTANGLES
    listManager.ResizeRectangles();

    // CLEAR BACKGROUND
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    for (const Rect::Rectangle& rect : items) {
        DrawRect(rect);
    }
}

void Renderer::DrawRect(const Rect::Rectangle& rect) {
    SDL_FRect sdl_rectangle = {
        static_cast<float>(rect.startX),
        static_cast<float>(rect.startY),
        static_cast<float>(rect.width),
        static_cast<float>(rect.height)
    };

    // GET THE COLOR BASED ON RECTANGLE STATE
    Color::RGB_Color color = Color::GetRectangleColor(rect.state);
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, 255);

    // DRAW THE RECTANGLE TO SCREEN
    SDL_RenderFillRect(renderer, &sdl_rectangle);
}
