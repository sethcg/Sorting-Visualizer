#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <algorithm>
#include <vector>

#include <Rect.hpp>
#include <Sort.hpp>

class Bubble : public Sort {
    public:
        virtual const char* GetName() const override { return "Bubble"; }

    protected:
        virtual void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;
};

#endif