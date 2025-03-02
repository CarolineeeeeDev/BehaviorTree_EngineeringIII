#include "BTTasks.h"
#include "AICharacter.h"
#include "CustomAIController.h"

bool UPatrolTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->Patrol();
    return true;
}

bool UChaseTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->ChasePlayer();
    return true;
}

bool USearchTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->SearchArea();
    return true;
}

bool UAttackTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->Attack();
    return true;
}

bool UDefendTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->Defend();
    return true;
}

bool URechargeTask::Execute(AAICharacter* AI) {
    if (!AI) return false;
    AI->Recharge();
    return true;
}
