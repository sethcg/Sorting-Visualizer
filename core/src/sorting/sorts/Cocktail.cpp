#include <algorithm>
#include <vector>

#include <Cocktail.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

void Cocktail::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    size_t start = 0;
    size_t end = array.size() - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

        // LEFT TO RIGHT PASS
        for (size_t i = start; i < end; ++i) {

            // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP BEFORE SWAP
            array[i].state = Rect::State::SELECTED;
            array[i + 1].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            if (array[i].value > array[i + 1].value) {
                std::swap(array[i], array[i + 1]);
                swapped = true;

                // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP AFTER SWAP
                array[i].state = Rect::State::BASE;
                array[i + 1].state = Rect::State::SELECTED;
                PushStep(sequence, array);
            }

            // RESET STATE AFTER COMPARISON
            array[i].state = Rect::State::BASE;
            array[i + 1].state = Rect::State::BASE;
        }

        // MARK ELEMENT AT END AS ORDERED
        array[end].state = Rect::State::ORDERED;
        PushStep(sequence, array);

        if (!swapped) break;
        swapped = false;
        --end;

        // RIGHT TO LEFT PASS
        for (size_t i = end; i > start; --i) {

            // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP BEFORE SWAP
            array[i - 1].state = Rect::State::COMPARED;
            array[i].state = Rect::State::SELECTED;
            PushStep(sequence, array);

            if (array[i - 1].value > array[i].value) {
                std::swap(array[i - 1], array[i]);
                swapped = true;

                // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP AFTER SWAP
                array[i - 1].state = Rect::State::SELECTED;
                array[i].state = Rect::State::BASE;
                PushStep(sequence, array);
            }

            // RESET STATE AFTER COMPARISON
            array[i - 1].state = Rect::State::BASE;
            array[i].state = Rect::State::BASE;
        }

        // MARK ELEMENT AT START AS ORDERED
        array[start].state = Rect::State::ORDERED;
        PushStep(sequence, array);

        ++start;
    }

    // MARK ALL REMAINING AS ORDERED
    for (auto& rect : array) {
        rect.state = Rect::State::ORDERED;
    }
}
