#ifndef RECT_H
#define RECT_H

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

#define rect_base_color rgb_color { .r = 50, .g = 50, .b = 50 }

// OTHER COLORS TO BETTER DISTINGUISH THE SORTING PROCESS
#define rect_green_color rgb_color { .r = 0, .g = 255, .b = 75 }
#define rect_blue_color rgb_color { .r = 0, .g = 180, .b = 225 }
#define rect_orange_color rgb_color { .r = 255, .g = 150, .b = 0 }

typedef struct {
    int value;
    int width;
    int height;
    int start_x;    // TOP-LEFT X COORDINATE
    int start_y;    // TOP-LEFT Y COORDINATE
    rgb_color rect_color;
} Rectangle;

#endif