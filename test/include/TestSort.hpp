#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <memory>
#include <vector>

#include <Rect.hpp>
#include <ListManager.hpp>
#include <Sort.hpp>

namespace TestSort {

    static const int LIST_SIZE = 10;

    SortSequence GenerateSequence(Sort::Sort* sort) {
        // CREATE MOCK RECTANGLE LIST
        std::vector<Rect::Rectangle> rects;
        rects.reserve(LIST_SIZE);
        for (int i = 0; i < LIST_SIZE; ++i) {
            Rect::Rectangle rect;
            rect.value = i + 1;
            rect.state = Rect::State::BASE;
            rects.push_back(rect);
        }

        // GENERATE SORT SEQUENCE
        SortSequence sequence;
        sort->SetSequence(&sequence, rects);
        return sequence;
    }

}

#endif