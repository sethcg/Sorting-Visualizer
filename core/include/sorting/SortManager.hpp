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
#include <Quick.hpp>
#include <Selection.hpp>

class SortManager {
    public:
        SortManager() {
            sorts[0] = std::make_unique<Bubble>();
            sorts[1] = std::make_unique<Cocktail>();
            sorts[2] = std::make_unique<Insertion>();
            sorts[3] = std::make_unique<Quick>();
            sorts[4] = std::make_unique<Selection>();
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
        std::array<std::unique_ptr<Sort>, 5> sorts;
        std::unique_ptr<SortSequence> sortSequence;
};

#endif
