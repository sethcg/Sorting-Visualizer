#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>
#include <vector>
#include <memory>

#include <Rect.hpp>
#include <Sort.hpp>

class Selection : public Sort {
    public:
        const char* GetName() const override { return "Selection"; }

    protected:
        void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;
};


#endif