#ifndef COCKTAIL_SORT_H
#define COCKTAIL_SORT_H

#include <vector>
#include <memory>

#include <Sort.hpp>
#include <Rect.hpp>

class Cocktail : public Sort {
    public:
        virtual const char* GetName() const override { return "Cocktail"; }

    protected:
        virtual void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;
};

#endif