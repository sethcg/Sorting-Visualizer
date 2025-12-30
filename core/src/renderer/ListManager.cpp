#include <algorithm>
#include <vector>

#include <SDL3/SDL.h>

#include <ListManager.hpp>
#include <Rect.hpp>

void ListManager::CreateList() {
    rects.clear();
    rects.reserve(listCount);

    int drawableWidth = windowWidth - (margin * 2);
    int drawableHeight = windowHeight - (margin * 2) - (windowHeight / 10);

    int rectWidth = (drawableWidth - rectPadding * (listCount - 1)) / listCount;
    int widthOffset = (drawableWidth - (listCount * (rectWidth + rectPadding))) / 2;

    for (int i = 0; i < listCount; ++i) {
        int rectHeight = (i + 1) * (drawableHeight / listCount);
        Rect::Rectangle rect;
        rect.value = i + 1;
        rect.width = rectWidth;
        rect.height = rectHeight;
        rect.startX = margin + (i * (rectWidth + rectPadding)) + widthOffset;
        rect.startY = margin + (drawableHeight - rectHeight) + (windowHeight / 10);
        rect.state = Rect::State::BASE;
        rects.push_back(rect);
    }
}

void ListManager::Resize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    ResizeRectangles();
}

void ListManager::ResizeRectangles() {
    int drawableWidth = windowWidth - (margin * 2);
    int drawableHeight = windowHeight - (margin * 2) - (windowHeight / 10);

    int rectWidth = (drawableWidth - rectPadding * (listCount - 1)) / listCount;
    int widthOffset = (drawableWidth - (listCount * (rectWidth + rectPadding))) / 2;

    for (int i = 0; i < listCount; ++i) {
        int rectHeight = rects[i].value * (drawableHeight / listCount);
        rects[i].width = rectWidth;
        rects[i].height = rectHeight;
        rects[i].startX = margin + (i * (rectWidth + rectPadding)) + widthOffset;
        rects[i].startY = margin + (drawableHeight - rectHeight) + (windowHeight / 10);
    }
}

void ListManager::Shuffle() {
    // FISHER-YATES SHUFFLE
    int j, temp = 0;
    for (int i = listCount - 1; i > 0; i--) {
        j = rand() % (i + 1);

        // SWAP VALUES
        temp = rects[i].value;
        rects[i].value = rects[j].value;
        rects[j].value = temp;
    }

    for (Rect::Rectangle& rect : rects) {
        rect.state = Rect::State::BASE;
    }

    // UPDATE HEIGHTS AND X/Y POSITIONING AFTER SHUFFLE
    Resize(windowWidth, windowHeight);
}