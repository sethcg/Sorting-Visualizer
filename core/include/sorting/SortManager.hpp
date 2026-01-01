#ifndef SORT_MANAGER_H
#define SORT_MANAGER_H

#include <array>
#include <memory>
#include <vector>

#include <Rect.hpp>
#include <Sort.hpp>

#include <Bubble.hpp>
#include <Cocktail.hpp>
#include <Insertion.hpp>
#include <Selection.hpp>
// #include <Heap.hpp>
// #include <Merge.hpp>
// #include <Quick.hpp>
// #include <Radix.hpp>

class SortManager {
    public:
        SortManager() {
            // ARRAY OF SORTING ALGORITHMS
            initializedCount = 4;
            sorts[0] = std::make_unique<Bubble>();
            sorts[1] = std::make_unique<Cocktail>();
            sorts[2] = std::make_unique<Insertion>();
            sorts[3] = std::make_unique<Selection>();
            // sorts[4] = std::make_unique<HeapSort>();
            // sorts[5] = std::make_unique<MergeSort>();
            // sorts[6] = std::make_unique<QuickSort>();
            // sorts[7] = std::make_unique<RadixSort>();
        }

        const char* GetSortName(int sortId) const;

        int GetSortCount() const;

        void SetSort(int sortId);

        void GenerateSequence(const std::vector<Rect::Rectangle>& rects);

        void Step(std::vector<Rect::Rectangle>& rects, int index);

        bool IncrementStep(std::vector<Rect::Rectangle>& rects);

    public:
        int stepIndex = 0;
        int currentSortId = 0;

    private:
        int initializedCount = 0;
        std::array<std::unique_ptr<Sort>, 8> sorts;
        std::unique_ptr<SortSequence> sortSequence;
};

#endif
