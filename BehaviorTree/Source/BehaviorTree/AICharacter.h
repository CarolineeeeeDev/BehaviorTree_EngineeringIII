#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTreeNode.h"
#include "AICharacter.generated.h"

UENUM(BlueprintType)
enum class EAIType : uint8 {
    Guard UMETA(DisplayName = "Guard"),
    Robot UMETA(DisplayName = "Robot")
};

UCLASS()
class BEHAVIORTREE_API AAICharacter : public ACharacter {
    GENERATED_BODY()

public:
    AAICharacter();

    UPROPERTY(BlueprintReadWrite)
    float RobotPower;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    void InitializeBehaviorTree();

    UPROPERTY(EditAnywhere, Category = "AI")
    EAIType AIType;

    UPROPERTY()
    TObjectPtr<UPawnSensingComponent> PawnSensingComponent;

    UPROPERTY()
    TObjectPtr<UBehaviorTreeNode> RootNode;


public:
    UFUNCTION()
    void OnSeePawn(APawn* SeenPawn);

    UFUNCTION()
    void OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);

    void Patrol();
    void ChasePlayer();
    void SearchArea();
    UFUNCTION(BlueprintImplementableEvent)
    void AttackEvent();
    UFUNCTION(BlueprintImplementableEvent)
    void RechargeEvent();
    UFUNCTION(BlueprintImplementableEvent)
    void DefendEvent();
    void Attack();
    void LookAround();
    void Recharge();

    bool CanSeePlayer();
    bool HeardNoise();

    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<APawn> TargetPlayer;

    FVector LastNoiseLocation;
    int CurrentPatrolIndex = 0;

    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<AActor*> PatrolPoints;
};