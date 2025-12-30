#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include <algorithm>
#include <vector>

#include <SDL3/SDL.h>

#include <Rect.hpp>

class ListManager {
    public:
        ListManager(int windowWidth, int windowHeight, int listCount = 32) {
            this->windowWidth = windowWidth;
            this->windowHeight = windowHeight;
            this->listCount = listCount;
            CreateList();
        }

        void CreateList();

        void Resize(int width, int height);

        void ResizeRectangles();

        void Shuffle();

        std::vector<Rect::Rectangle>& GetItems() { return rects; }

    private:
        int listCount;
        int windowWidth;
        int windowHeight;

        int margin = 24;
        int rectPadding = 2;

        std::vector<Rect::Rectangle> rects;
};

#endif