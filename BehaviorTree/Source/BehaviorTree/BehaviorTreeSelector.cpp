#include "BehaviorTreeSelector.h"

void UBehaviorTreeSelector::AddChild(UBehaviorTreeNode* Child) {
    if (Child) {
        Children.Add(Child);
    }
}

bool UBehaviorTreeSelector::Execute(AAICharacter* AI) {
    for (UBehaviorTreeNode* Child : Children) {
        if (Child && Child->Execute(AI)) {
            return true;
        }
    }
    return false;
}
