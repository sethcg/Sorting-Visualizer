#ifndef SORT_MANAGER_H
#define SORT_MANAGER_H

#include <array>
#include <memory>
#include <vector>

#include <Rect.hpp>
#include <Sort.hpp>

#include <Bubble.hpp>
// #include <CocktailSort.hpp>
// #include <HeapSort.hpp>
// #include <InsertionSort.hpp>
// #include <MergeSort.hpp>
// #include <QuickSort.hpp>
// #include <RadixSort.hpp>
// #include <SelectionSort.hpp>

class SortManager {
    public:
        SortManager() {
            // ARRAY OF SORTING ALGORITHMS
            initializedCount = 1;
            sorts[0] = std::make_unique<Bubble>();
            // sorts[1] = std::make_unique<CocktailSort>();
            // sorts[2] = std::make_unique<HeapSort>();
            // sorts[3] = std::make_unique<InsertionSort>();
            // sorts[4] = std::make_unique<MergeSort>();
            // sorts[5] = std::make_unique<QuickSort>();
            // sorts[6] = std::make_unique<RadixSort>();
            // sorts[7] = std::make_unique<SelectionSort>();
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
        std::array<std::unique_ptr<Sort::Sort>, 8> sorts;
        std::unique_ptr<SortSequence> sortSequence;
};

#endif
