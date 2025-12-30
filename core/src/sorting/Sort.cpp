#include <memory>
#include <vector>

#include <Sort.hpp>
#include <Rect.hpp>

namespace Sort {

    void Sort::PushStep(SortSequence& sequence, std::vector<Rect::Rectangle> rects) {
        if (!sequence.steps) {
            sequence.steps = std::make_unique<std::vector<SortStep>>();
        }

        // PUSH SORT STEP TO THE SEQUENCE
        sequence.steps->emplace_back(SortStep { 
            std::make_unique<std::vector<Rect::Rectangle>>(std::move(rects)) 
        });

        // INCREMENT STEP COUNT
        ++sequence.stepCount;
    }

    void Sort::FirstStep(SortSequence& sequence, const std::vector<Rect::Rectangle>& rects) {
        PushStep(sequence, rects);
    }

    void Sort::LastStep(SortSequence& sequence, std::vector<Rect::Rectangle>& rects) {
        for (Rect::Rectangle& rectangle : rects) {
            rectangle.state = Rect::State::ORDERED;
        }
        PushStep(sequence, rects);
    }

}
