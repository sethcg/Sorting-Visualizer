#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include <memory>

#include <Sort.hpp>
#include <Rect.hpp>

class Merge : public Sort {
    public:
        const char* GetName() const override { return "Merge"; }

    protected:
        void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;

    private:
        void MergeSort(std::vector<Rect::Rectangle>& array, std::vector<Rect::Rectangle>& buffer, size_t left, size_t right, SortSequence& sequence);

        void MergeRanges(std::vector<Rect::Rectangle>& array, std::vector<Rect::Rectangle>& buffer,size_t left, size_t mid, size_t right, SortSequence& sequence);
};

#endif