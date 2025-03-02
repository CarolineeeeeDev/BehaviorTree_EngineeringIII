#include "BTConditions.h"
#include "AICharacter.h"

bool USeePlayerCondition::Execute(AAICharacter* AI) {
    if (!AI) return false;
    return AI->CanSeePlayer();
}

bool UHearNoiseCondition::Execute(AAICharacter* AI) {
    if (!AI) return false;
    return AI->HeardNoise();
}
