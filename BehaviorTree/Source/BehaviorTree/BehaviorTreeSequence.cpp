#include "BehaviorTreeSequence.h"

void UBehaviorTreeSequence::AddChild(UBehaviorTreeNode* Child) {
    if (Child) {
        Children.Add(Child);
    }
}

bool UBehaviorTreeSequence::Execute(AAICharacter* AI) {
    for (UBehaviorTreeNode* Child : Children) {
        if (!Child || !Child->Execute(AI)) {
            return false;
        }
    }
    return true;
}
