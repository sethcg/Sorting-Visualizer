#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <algorithm>
#include <vector>
#include <cstddef>

#include <Sort.hpp>
#include <Rect.hpp>

class Heap : public Sort {
    public:
        const char* GetName() const override { return "Heap"; }

    protected:
        void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;

    private:
        void Heapify(std::vector<Rect::Rectangle>& array, size_t heapSize, size_t root, SortSequence& sequence);
};

#endif
