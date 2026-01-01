#include <algorithm>
#include <vector>
#include <memory>

#include <Selection.hpp>
#include <Sort.hpp>
#include <Rect.hpp>

void Selection::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    const size_t size = array.size();

    for (size_t i = 0; i < size - 1; ++i) {
        size_t minIndex = i;

        // HIGHLIGHT INITIAL SELECTED MINIMUM
        array[minIndex].state = Rect::State::SELECTED;
        PushStep(sequence, array);

        for (size_t j = i + 1; j < size; ++j) {
            // HIGHLIGHT SEARCH FOR MINIMUM
            array[j].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            if (array[j].value < array[minIndex].value) {
                // UNHIGHLIGHT OLD SELECTED MINIMUM
                array[minIndex].state = Rect::State::BASE;
                minIndex = j;

                // HIGHLIGHT NEW SELECTED MINIMUM
                array[minIndex].state = Rect::State::SELECTED;
                PushStep(sequence, array);
            } else {
                // RESET STATE WHEN NOT SWAPPED
                array[j].state = Rect::State::BASE;
            }
        }

        // SWAP MINIMUM INTO PLACE
        if (minIndex != i) {
            std::swap(array[i], array[minIndex]);
            PushStep(sequence, array);
        }

        // MARK ELEMENT AS ORDERED
        array[i].state = Rect::State::ORDERED;

        // RESET STATES FOR NEXT ITERATION
        for (size_t k = i + 1; k < size; ++k) {
            if (array[k].state != Rect::State::ORDERED)
                array[k].state = Rect::State::BASE;
        }

        PushStep(sequence, array);
    }

    // ENSURE ALL ELEMENTS ARE MARKED ORDERED
    for (auto& rect : array) {
        rect.state = Rect::State::ORDERED;
    }
}
