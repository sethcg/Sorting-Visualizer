#ifndef COCKTAIL_SORT_H
#define COCKTAIL_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace CocktailSort {

    int GetStepCount(Rectangle* items);

    SortSequence GetSequence(Rectangle* items);

}

#endif