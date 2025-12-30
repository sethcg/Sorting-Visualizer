#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <memory>

#include <Sort.hpp>
#include <Rect.hpp>

class Bubble : public Sort::Sort {
    public:
        virtual const char* GetName() const override { return "Bubble"; }

        virtual void SetSequence(SortSequence* sequence, std::vector<Rect::Rectangle> rects) override;

    private:
        void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence);
};

#endif