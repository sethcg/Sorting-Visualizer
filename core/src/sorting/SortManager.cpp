
#include <array>
#include <memory>
#include <vector>

#include <Rect.hpp>
#include <Sort.hpp>
#include <SortManager.hpp>

const char* SortManager::GetSortName(int sortId) const {
    return sorts[sortId]->GetName();
}

int SortManager::GetSortCount() const {
    return initializedCount;
}

void SortManager::SetSort(int sortId) {
    if (sortId >= 0 && sortId < static_cast<int>(sorts.size())) {
        currentSortId = sortId;
    }
}

void SortManager::GenerateSequence(const std::vector<Rect::Rectangle>& rects) {
    sortSequence = std::make_unique<SortSequence>();
    if (currentSortId >= 0 && currentSortId < static_cast<int>(sorts.size())) {
        sorts[currentSortId]->SetSequence(sortSequence.get(), rects);
    }
}

void SortManager::Step(std::vector<Rect::Rectangle>& rects, int index) {
    if (!sortSequence || !sortSequence->steps) return;
    if (index < 0 || index >= sortSequence->stepCount) return;

    stepIndex = index;

    const std::vector<Rect::Rectangle>& stepRects = *(sortSequence->steps->at(index).rects);
    for (size_t i = 0; i < stepRects.size(); ++i) {
        rects[i] = stepRects[i];
    }
}

bool SortManager::IncrementStep(std::vector<Rect::Rectangle>& rects) {
    if (!sortSequence || !sortSequence->steps) return true;
    if (stepIndex >= sortSequence->stepCount) return true;

    Step(rects, ++stepIndex);

    // RETURN TRUE WHEN SORTING IS COMPLETE
    return stepIndex >= sortSequence->stepCount;
}
