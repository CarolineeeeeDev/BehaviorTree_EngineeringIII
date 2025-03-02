#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeNode.h"
#include "BTTasks.generated.h"

class AAICharacter;

UCLASS()
class BEHAVIORTREE_API UPatrolTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API UChaseTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API USearchTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API UAttackTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API UDefendTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};

UCLASS()
class BEHAVIORTREE_API URechargeTask : public UBehaviorTreeNode {
    GENERATED_BODY()
public:
    virtual bool Execute(AAICharacter* AI) override;
};
