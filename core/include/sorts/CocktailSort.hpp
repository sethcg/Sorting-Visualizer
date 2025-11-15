#ifndef COCKTAIL_SORT_H
#define COCKTAIL_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace CocktailSort {

    int GetStepCount_CocktailSort(Rectangle* items);

    SortSequence GetSequence_CocktailSort(Rectangle* items);

}

#endif