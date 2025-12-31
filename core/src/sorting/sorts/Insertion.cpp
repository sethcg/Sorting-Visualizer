#include <algorithm>
#include <vector>

#include <Insertion.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

void Insertion::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    const size_t size = array.size();

    for (size_t i = 1; i < size; ++i) {
        Rect::Rectangle key = array[i];
        size_t j = i;

        // HIGHLIGHT THE KEY ELEMENT
        array[i].state = Rect::State::SELECTED;
        PushStep(sequence, array);

        // SHIFT ELEMENTS TO THE RIGHT
        while (j > 0 && array[j - 1].value > key.value) {

            // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP BEFORE SWAP
            array[j].state = Rect::State::SELECTED;
            array[j - 1].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            // RESET STATE AFTER COMPARISON
            array[j - 1].state = Rect::State::BASE;

            array[j] = array[j - 1];
            --j;

            // HIGHLIGHT ELEMENTS BEING COMPARED, RECORD STEP AFTER SWAP
            array[j].state = Rect::State::SELECTED;
            PushStep(sequence, array);
        }

        // INSERT KEY INTO CORRECT POSITION
        array[j] = key;
        
        // RESET STATES FOR NEXT ITERATION
        for (size_t k = 0; k < size; ++k) {
            if (array[k].state != Rect::State::ORDERED)
                array[k].state = Rect::State::BASE;
        }
    }

    // ENSURE ALL ELEMENTS ARE MARKED ORDERED
    for (auto& rect : array) {
        rect.state = Rect::State::ORDERED;
    }
}
