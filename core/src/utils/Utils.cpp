#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

#include <Utils.hpp>

void Swap(Rectangle* array, int index_one, int index_two) {
    int temp = array[index_one].value;
    array[index_one].value = array[index_two].value;
    array[index_two].value = temp;
}

rgb_color GetRectangleColor(bool isOrdered, bool isCurrent, bool isChecking) {
    return 
        isOrdered ? rect_green_color : 
        isCurrent ? rect_blue_color : 
        isChecking ? rect_orange_color : rect_base_color;
}