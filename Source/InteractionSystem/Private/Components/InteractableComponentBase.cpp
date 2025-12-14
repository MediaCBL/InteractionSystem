// © Felix Courteau-Boutin All Right Reserved

#include "Components/InteractableComponentBase.h"

UInteractableComponentBase::UInteractableComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponentBase::PerformInteraction(AActor* InstigatorActor, AController* InstigatorController)
{
	if (!bIsEnabled || !GetOwner())
	{
		return;
	}

	OnInteraction.Broadcast(this, InstigatorActor, InstigatorController);
}
