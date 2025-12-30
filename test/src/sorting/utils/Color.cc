#include <gtest/gtest.h>

#include <Color.hpp>
#include <Rect.hpp>

using namespace Color;

void ValidateColor(const Color::RGB_Color& color, const Color::RGB_Color& expected) {
    EXPECT_EQ(color.R, expected.R);
    EXPECT_EQ(color.G, expected.G);
    EXPECT_EQ(color.B, expected.B);
}

TEST(Color_Test, GetRectangleColorReturnsExpected) {
    ValidateColor(GetRectangleColor(Rect::State::ORDERED),  GREEN);
    ValidateColor(GetRectangleColor(Rect::State::SELECTED), RED);
    ValidateColor(GetRectangleColor(Rect::State::COMPARED), BLUE);
    ValidateColor(GetRectangleColor(Rect::State::GROUPING), ORANGE);
    ValidateColor(GetRectangleColor(Rect::State::BASE),     BASE);
}