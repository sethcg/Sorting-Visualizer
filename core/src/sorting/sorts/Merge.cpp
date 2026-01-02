#include <vector>
#include <memory>

#include <Merge.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

void Merge::RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) {
    if (array.empty()) return;

    std::vector<Rect::Rectangle> buffer(array.size());
    MergeSort(array, buffer, 0, array.size() - 1, sequence);

    // ENSURE ALL ELEMENTS ARE MARKED ORDERED
    for (Rect::Rectangle& rect : array) {
        rect.state = Rect::State::ORDERED;
    }
    PushStep(sequence, array);
}

void Merge::MergeSort(std::vector<Rect::Rectangle>& array, std::vector<Rect::Rectangle>& buffer, size_t left, size_t right, SortSequence& sequence) {
    if (left >= right) return;

    size_t mid = (left + right) / 2;

    MergeSort(array, buffer, left, mid, sequence);
    MergeSort(array, buffer, mid + 1, right, sequence);
    MergeRanges(array, buffer, left, mid, right, sequence);
}

static void ResetNonOrdered(std::vector<Rect::Rectangle>& array) {
    for (Rect::Rectangle& rect : array) {
        if (rect.state != Rect::State::ORDERED) {
            rect.state = Rect::State::BASE;
        }
    }
}

void Merge::MergeRanges(std::vector<Rect::Rectangle>& array, std::vector<Rect::Rectangle>& buffer, size_t left, size_t mid, size_t right, SortSequence& sequence) {
    // HIGHLIGHT MERGE RANGE (LEFT/RIGHT HALVES)
    ResetNonOrdered(array);
    for (size_t x = left; x <= right; ++x) {
        array[x].state = (x <= mid) ? Rect::State::MERGE_LEFT : Rect::State::MERGE_RIGHT;
    }
    PushStep(sequence, array);

    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;

    while (i <= mid && j <= right) {
        for (size_t x = left; x <= right; ++x) {
            if (array[x].state == Rect::State::SELECTED ||
                array[x].state == Rect::State::COMPARED) {
                array[x].state = (x <= mid)
                    ? Rect::State::MERGE_LEFT
                    : Rect::State::MERGE_RIGHT;
            }
        }

        // SINGLE SELECTED / COMPARED
        array[i].state = Rect::State::SELECTED;
        array[j].state = Rect::State::COMPARED;
        PushStep(sequence, array);

        if (array[i].value <= array[j].value) {
            buffer[k++] = array[i++];
        } else {
            buffer[k++] = array[j++];
        }

        // SHOW MERGED PREFIX (GROWING)
        for (size_t x = left; x < k; ++x) {
            array[x].state = Rect::State::GROUPING;
        }
        PushStep(sequence, array);
    }

    // COPY REMAINDERS
    while (i <= mid) buffer[k++] = array[i++];
    while (j <= right) buffer[k++] = array[j++];

    // FINAL COPY BACK — SINGLE STEP
    ResetNonOrdered(array);
    for (size_t x = left; x <= right; ++x) {
        array[x] = buffer[x];
        array[x].state = Rect::State::GROUPING;
    }
    PushStep(sequence, array);
}
