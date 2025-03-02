#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BehaviorTreeNode.generated.h"

class AAICharacter;

UCLASS(Abstract)
class BEHAVIORTREE_API UBehaviorTreeNode : public UObject {
    GENERATED_BODY()

public:
    virtual bool Execute(AAICharacter* AI) { return false; }
};
