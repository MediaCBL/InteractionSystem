// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "InteractionColliderInterface.h"
#include "Components/SphereComponent.h"
#include "SphereInteractionColliderComponent.generated.h"

/**
 * Sphere-based interaction collider.
 */
UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API USphereInteractionColliderComponent
	: public USphereComponent, public IInteractionColliderInterface
{
	GENERATED_BODY()

public:
	USphereInteractionColliderComponent();
};
