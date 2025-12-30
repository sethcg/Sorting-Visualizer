#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

// FORWARD DECLARATION
namespace Rect {
    enum class State;
}

namespace Color {

    struct RGB_Color {
        uint8_t R;
        uint8_t G;
        uint8_t B;
    };

    inline constexpr RGB_Color BASE   { 50,  50,  50  };
    inline constexpr RGB_Color RED    { 200, 60,  40  };
    inline constexpr RGB_Color GREEN  { 0,   150, 75  };
    inline constexpr RGB_Color BLUE   { 0,   120, 160 };
    inline constexpr RGB_Color ORANGE { 200, 120, 0   };

    RGB_Color GetRectangleColor(Rect::State state);

}

#endif