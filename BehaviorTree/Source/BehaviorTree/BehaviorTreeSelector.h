#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeNode.h"
#include "BehaviorTreeSelector.generated.h"

UCLASS()
class BEHAVIORTREE_API UBehaviorTreeSelector : public UBehaviorTreeNode {
    GENERATED_BODY()

public:
    void AddChild(UBehaviorTreeNode* Child);

    virtual bool Execute(AAICharacter* AI) override;

private:
    UPROPERTY()
    TArray<UBehaviorTreeNode*> Children;
};
