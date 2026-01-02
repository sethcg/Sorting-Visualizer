#include <Color.hpp>
#include <Rect.hpp>

namespace Color {

    RGB_Color GetRectangleColor(Rect::State state) {
        switch (state) {
            case Rect::State::ORDERED:  return GREEN;
            case Rect::State::SELECTED: return RED;
            case Rect::State::COMPARED: return BLUE;
            case Rect::State::GROUPING: return ORANGE;
            case Rect::State::MERGE_LEFT: return CYAN;
            case Rect::State::MERGE_RIGHT: return PURPLE;
            default:                    return BASE;
        }
    }

}