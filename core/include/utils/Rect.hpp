#ifndef RECT_H
#define RECT_H

#define RECT_WIDTH 16

typedef struct {
    int index;
    int height;
    int start_x;    // TOP-LEFT X COORDINATE
    int start_y;    // TOP-LEFT Y COORDINATE
} rectangle;

#endif