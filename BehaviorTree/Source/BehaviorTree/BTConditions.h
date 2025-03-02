#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeNode.h"
#include "BTConditions.generated.h"

UCLASS()
class BEHAVIORTREE_API USeePlayerCondition : public UBehaviorTreeNode {
    GENERATED_BODY()

public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API UHearNoiseCondition : public UBehaviorTreeNode {
    GENERATED_BODY()

public:
    virtual bool Execute(AAICharacter* AI) override;
};
