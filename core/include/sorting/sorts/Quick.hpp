#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <algorithm>
#include <vector>
#include <cstddef>

#include <Sort.hpp>
#include <Rect.hpp>

class Quick : public Sort {
    public:
        const char* GetName() const override { return "Quick"; }

    protected:
        void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;

    private:
        void QuickSort(std::vector<Rect::Rectangle>& array, size_t low, size_t high, SortSequence& sequence);

        size_t Partition(std::vector<Rect::Rectangle>& array, size_t low, size_t high, SortSequence& sequence);
};

#endif
