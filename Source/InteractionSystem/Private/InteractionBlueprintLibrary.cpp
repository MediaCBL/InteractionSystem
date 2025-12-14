// © Felix Courteau-Boutin All Right Reserved

#include "InteractionBlueprintLibrary.h"
#include "Components/InteractableComponent.h"

UInteractableComponent* UInteractionBlueprintLibrary::GetFirstInteractableComponent(AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<UInteractableComponent>() : nullptr;
}

bool UInteractionBlueprintLibrary::IsCloserInteraction(const FInteractionResult& A, const FInteractionResult& B)
{
	return A.Distance < B.Distance;
}

