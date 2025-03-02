#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BTConditions.h"
#include "BTTasks.h"
#include "BehaviorTreeSelector.h"
#include "BehaviorTreeSequence.h"
#include "CustomAIController.h"

AAICharacter::AAICharacter() {
    PrimaryActorTick.bCanEverTick = true;

    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
    if (PawnSensingComponent) {
        PawnSensingComponent->SightRadius = 500.0f;
        PawnSensingComponent->HearingThreshold = 900.0f;
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePawn);
        PawnSensingComponent->OnHearNoise.AddDynamic(this, &AAICharacter::OnHearNoise);
    }
}

void AAICharacter::BeginPlay() {
    Super::BeginPlay();
    InitializeBehaviorTree();
}

void AAICharacter::InitializeBehaviorTree() {
    if (AIType == EAIType::Guard) {
        UBehaviorTreeSelector* Root = NewObject<UBehaviorTreeSelector>(this);

        UBehaviorTreeSequence* GuardLogic = NewObject<UBehaviorTreeSequence>(this);
        GuardLogic->AddChild(NewObject<USeePlayerCondition>(this));
        GuardLogic->AddChild(NewObject<UChaseTask>(this));

        UBehaviorTreeSequence* SearchLogic = NewObject<UBehaviorTreeSequence>(this);
        SearchLogic->AddChild(NewObject<UHearNoiseCondition>(this));
        SearchLogic->AddChild(NewObject<USearchTask>(this));

        Root->AddChild(GuardLogic);
        Root->AddChild(SearchLogic);
        Root->AddChild(NewObject<UPatrolTask>(this));

        RootNode = Root;

        UE_LOG(LogTemp, Warning, TEXT("Guard logic initialized with Patrol, Chase, and Search tasks."));
    }
    else if (AIType == EAIType::Robot) {
        UBehaviorTreeSelector* Root = NewObject<UBehaviorTreeSelector>(this);

        UBehaviorTreeSequence* RobotLogic = NewObject<UBehaviorTreeSequence>(this);
        RobotLogic->AddChild(NewObject<USeePlayerCondition>(this));
        RobotLogic->AddChild(NewObject<UAttackTask>(this));

        UBehaviorTreeSequence* DefenseLogic = NewObject<UBehaviorTreeSequence>(this);
        DefenseLogic->AddChild(NewObject<UDefendTask>(this));
        DefenseLogic->AddChild(NewObject<URechargeTask>(this));

        Root->AddChild(RobotLogic);
        Root->AddChild(DefenseLogic);

        RootNode = Root;

        UE_LOG(LogTemp, Warning, TEXT("Robot logic initialized with Attack and Defense tasks."));
    }
}

void AAICharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (RootNode) {
        RootNode->Execute(this);
    }
}

void AAICharacter::Patrol() {
    if (PatrolPoints.Num() == 0) {
        UE_LOG(LogTemp, Warning, TEXT("No patrol points set for AI character."));
        return;
    }
    FVector TargetLocation = PatrolPoints[CurrentPatrolIndex]->GetActorLocation();
    float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation);

    if (DistanceToTarget < 100.0f) {
        CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();
        TargetLocation = PatrolPoints[CurrentPatrolIndex]->GetActorLocation();
    }

    ACustomAIController* AIController = Cast<ACustomAIController>(GetController());
    if (AIController) {
        AIController->MoveToLocation(TargetLocation);
    }
}


void AAICharacter::ChasePlayer() {
    if (TargetPlayer) {
        ACustomAIController* AIController = Cast<ACustomAIController>(GetController());
        if (AIController) {
            AIController->MoveToLocation(TargetPlayer->GetActorLocation());
        }
    }
}

void AAICharacter::SearchArea() {
    ACustomAIController* AIController = Cast<ACustomAIController>(GetController());
    if (AIController) {
        AIController->MoveToLocation(LastNoiseLocation);
        FVector TargetLocation = LastNoiseLocation;
        FVector CurrentLocation = GetActorLocation();
        float DistanceToTarget = FVector::Dist(FVector(CurrentLocation.X, CurrentLocation.Y, 0), FVector(TargetLocation.X, TargetLocation.Y, 0));

        if (DistanceToTarget < 120.0f) {
            LastNoiseLocation = FVector(0, 0, 0);
        }
    }
}


void AAICharacter::Attack() {
    if (TargetPlayer) {
        UE_LOG(LogTemp, Warning, TEXT("AI attacking player at location: %s"), *TargetPlayer->GetActorLocation().ToString());
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No player to attack!"));
    }
}

void AAICharacter::Defend() {
    UE_LOG(LogTemp, Warning, TEXT("AI is defending! (Invincible)"));
}

void AAICharacter::Recharge() {
    UE_LOG(LogTemp, Warning, TEXT("AI is recharging energy"));
}

bool AAICharacter::CanSeePlayer() {
    if (TargetPlayer) 
    {
        FVector TargetLocation = TargetPlayer->GetActorLocation();
        float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation);
        if (DistanceToTarget < 600.0f) return true;
    }
    return false;
}

bool AAICharacter::HeardNoise() {
    if (!LastNoiseLocation.IsZero()) {
        UE_LOG(LogTemp, Warning, TEXT("Heard noise at location: %s"), *LastNoiseLocation.ToString());
        return true;
    }
    return false;
}

void AAICharacter::OnSeePawn(APawn* SeenPawn) {
    if (SeenPawn->ActorHasTag("Player")) {
        TargetPlayer = SeenPawn;
    }
}

void AAICharacter::OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume) {
    LastNoiseLocation = Location;
}
