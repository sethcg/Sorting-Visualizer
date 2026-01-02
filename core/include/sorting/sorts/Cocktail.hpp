#ifndef COCKTAIL_SORT_H
#define COCKTAIL_SORT_H

#include <algorithm>
#include <vector>

#include <Rect.hpp>
#include <Sort.hpp>

class Cocktail : public Sort {
    public:
        virtual const char* GetName() const override { return "Cocktail"; }

    protected:
        virtual void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;
};

#endif