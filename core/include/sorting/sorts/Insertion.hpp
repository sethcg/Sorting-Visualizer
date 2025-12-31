#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <vector>
#include <memory>

#include <Sort.hpp>
#include <Rect.hpp>

class Insertion : public Sort {
    public:
        virtual const char* GetName() const override { return "Insertion"; }

    protected:
        virtual void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) override;
};

#endif