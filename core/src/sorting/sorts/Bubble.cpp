#include <algorithm>
#include <vector>
#include <memory>

#include <Bubble.hpp>
#include <Sort.hpp>
#include <Rect.hpp>

void Bubble::SetSequence(SortSequence* sequence, std::vector<Rect::Rectangle> rects) {
    if (!sequence) return;

    // RECORD FIRST STEP (UNSORTED)
    FirstStep(*sequence, rects);

    // RUN THE ALGORITHM, RECORDING STEPS DURING THE PROCESS
    RunSort(rects, *sequence);

    // RECORD LAST STEP (SORTED)
    LastStep(*sequence, rects);
}

void Bubble::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    const size_t arraySize = array.size();

    for (size_t i = 0; i < arraySize - 1; ++i) {
        bool swapped = false;

        for (size_t j = 0; j < arraySize - i - 1; ++j) {
            // HIGHLIGHT ELEMENTS BEING COMPARED
            array[j].state = Rect::State::SELECTED;
            array[j + 1].state = Rect::State::COMPARED;

            // RECORD STEP BEFORE SWAP
            PushStep(sequence, array);

            if (array[j].value > array[j + 1].value) {
                std::swap(array[j], array[j + 1]);
                swapped = true;

                // HIGHLIGHT ELEMENTS BEING COMPARED
                array[j].state = Rect::State::BASE;
                array[j + 1].state = Rect::State::SELECTED;

                // RECORD STEP AFTER SWAP
                PushStep(sequence, array);
            }

            // RESET STATE AFTER COMPARISON
            array[j].state = Rect::State::BASE;
            array[j + 1].state = Rect::State::BASE;
        }

        // MARK LAST ELEMENT AS ORDERED
        array[arraySize - i - 1].state = Rect::State::ORDERED;

        // RECORD AFTER EACH PASS (OPTIONAL)
        PushStep(sequence, array);

        if (!swapped) break;
    }

    // MARK REMAINING ELEMENTS AS ORDERED
    for (size_t i = 0; i < arraySize; ++i) {
        array[i].state = Rect::State::ORDERED;
    }
}
