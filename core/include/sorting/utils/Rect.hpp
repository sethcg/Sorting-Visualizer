#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Color.hpp>

namespace Rect {

    enum class State {
        BASE,
        SELECTED,
        COMPARED,
        GROUPING,
        MERGE_LEFT,
        MERGE_RIGHT,
        ORDERED
    };

    struct Rectangle {
        int value;
        int width;
        int height;
        int startX;     // TOP-LEFT X COORDINATE
        int startY;     // TOP-LEFT Y COORDINATE
        State state;    // SORTING STATE OF THE RECTANGLE

        Rectangle() {
            state = State::BASE;
        };
    };

}

#endif