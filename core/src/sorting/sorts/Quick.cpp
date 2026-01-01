#include <algorithm>
#include <Quick.hpp>

void Quick::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    if (array.empty()) return;

    QuickSort(array, 0, array.size() - 1, sequence);

    // ENSURE ALL ELEMENTS ARE MARKED ORDERED
    for (auto& rect : array) {
        rect.state = Rect::State::ORDERED;
    }
}

void Quick::QuickSort(std::vector<Rect::Rectangle>& array, size_t low, size_t high, SortSequence& sequence) {
    if (low >= high) {
        // HIGHLIGHT ORDERED ELEMENTS
        if (low < array.size()) {
            array[low].state = Rect::State::ORDERED;
        }     
        return;
    }

    size_t pivotIndex = Partition(array, low, high, sequence);
    if (pivotIndex > 0) {
        QuickSort(array, low, pivotIndex - 1, sequence);
    }

    QuickSort(array, pivotIndex + 1, high, sequence);
}

size_t Quick::Partition(std::vector<Rect::Rectangle>& array, size_t low, size_t high, SortSequence& sequence) {
    const int pivotValue = array[high].value;
    size_t i = low;

    // HIGHLIGHT PIVOT
    array[high].state = Rect::State::SELECTED;
    PushStep(sequence, array);

    for (size_t j = low; j < high; ++j) {

        // HIGHLIGHT ELEMENTS BEING GROUPED (VALUE LESS THAN CURRENT PIVOT)
        for (size_t k = low; k < i; ++k) {
            array[k].state = Rect::State::GROUPING;
        }
        for (size_t k = i; k < high; ++k) {
            if (array[k].state != Rect::State::GROUPING) {
                array[k].state = Rect::State::BASE;
            }
        }

        // HIGHLIGHT PIVOT
        array[high].state = Rect::State::SELECTED;

        // HIGHLIGHT ELEMENT BEING COMPARED
        array[j].state = Rect::State::COMPARED;
        PushStep(sequence, array);

        if (array[j].value < pivotValue) {
            std::swap(array[i], array[j]);

            // HIGHLIGHT ELEMENTS BEING GROUPED (VALUE LESS THAN CURRENT PIVOT)
            array[i].state = Rect::State::GROUPING;
            PushStep(sequence, array);

            ++i;
        }

        // RESET STATE
        array[j].state = Rect::State::BASE;
    }

    //  PLACE PIVOT IN CORRECT POSITION
    std::swap(array[i], array[high]);

    // RESET STATE
    array[high].state = Rect::State::BASE;
    array[i].state = Rect::State::ORDERED;
    PushStep(sequence, array);

    return i;
}
