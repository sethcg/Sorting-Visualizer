#include <algorithm>
#include <vector>
#include <cstddef>

#include <Sort.hpp>
#include <Rect.hpp>
#include <Heap.hpp>

static void ColorHeapRegion(std::vector<Rect::Rectangle>& array, size_t heapSize) {
    for (size_t i = 0; i < array.size(); ++i) {
        // NEVER CHANGE ORDERED ELEMENTS
        if (array[i].state == Rect::State::ORDERED) continue;
        if (i < heapSize) array[i].state = Rect::State::GROUPING;
    }
}

void Heap::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    const size_t n = array.size();
    if (n == 0) return;

    // BUILD MAX HEAP
    for (int i = (int)n / 2 - 1; i >= 0; --i) {
        ColorHeapRegion(array, n);
        Heapify(array, n, i, sequence);
    }

    // EXTRACT ELEMENTS FROM HEAP
    for (size_t end = n - 1; end > 0; --end) {
        ColorHeapRegion(array, n);

        // MOVE MAX TO END
        std::swap(array[0], array[end]);
        array[end].state = Rect::State::ORDERED;
        PushStep(sequence, array);

        // RESTORE HEAP PROPERTY
        Heapify(array, end, 0, sequence);
    }

    // FINAL ELEMENT
    array[0].state = Rect::State::ORDERED;
    PushStep(sequence, array);
}

void Heap::Heapify(std::vector<Rect::Rectangle>& array, size_t heapSize, size_t root, SortSequence& sequence) {
    size_t current = root;

    while (true) {
        ColorHeapRegion(array, heapSize);

        size_t left  = 2 * current + 1;
        size_t right = 2 * current + 2;
        size_t largest = current;

        // HIGHLIGHT ROOT
        array[current].state = Rect::State::SELECTED;
        PushStep(sequence, array);

        // COMPARE ROOT WITH LEFT CHILD
        if (left < heapSize) {
            array[left].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            if (array[left].value > array[largest].value) {
                largest = left;
            }
        }

        // COMPARE ROOT WITH RIGHT CHILD
        if (right < heapSize) {
            array[right].state = Rect::State::COMPARED;
            PushStep(sequence, array);

            if (array[right].value > array[largest].value) {
                largest = right;
            }
        }

        // ROOT ALREADY LARGEST, GO NEXT
        if (largest == current) {
            array[current].state = Rect::State::GROUPING;
            break;
        }

        // ELSE, SWAP ROOT WITH LARGEST CHILD
        std::swap(array[current], array[largest]);
        PushStep(sequence, array);

        current = largest;
    }
}
