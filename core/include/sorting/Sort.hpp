#ifndef SORT_H
#define SORT_H

#include <memory>
#include <vector>

#include <Rect.hpp>

// FORWARD DECLARATIONS
namespace Rect {
    enum class State;
    struct Rectangle;
}

struct SortStep {
    std::unique_ptr<std::vector<Rect::Rectangle>> rects;
};

struct SortSequence {
    int stepCount = 0;
    std::unique_ptr<std::vector<SortStep>> steps;
};

class Sort {
    public:
        virtual ~Sort() = default;

        virtual const char* GetName() const = 0;

        void SetSequence(SortSequence* sequence, std::vector<Rect::Rectangle> rects);

    protected:
        virtual void RunSort(std::vector<Rect::Rectangle>& array, SortSequence& sequence) = 0;

        static void PushStep(SortSequence& sequence, std::vector<Rect::Rectangle> rects);

    private:
        static void FirstStep(SortSequence& sequence, const std::vector<Rect::Rectangle>& rects);
        
        static void LastStep(SortSequence& sequence, std::vector<Rect::Rectangle>& rects);
};

#endif
