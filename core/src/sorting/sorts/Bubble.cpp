#include <algorithm>
#include <vector>

#include <Bubble.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

void Bubble::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    const size_t arraySize = array.size();

    for (size_t i = 0; i < arraySize - 1; ++i) {
        bool swapped = false;

        for (size_t j = 0; j < arraySize - i - 1; ++j) {

            // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP BEFORE SWAP
            array[j].state = Rect::State::SELECTED;
            array[j + 1].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            if (array[j].value > array[j + 1].value) {
                std::swap(array[j], array[j + 1]);
                swapped = true;

                // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP AFTER SWAP
                array[j].state = Rect::State::BASE;
                array[j + 1].state = Rect::State::SELECTED;
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
