// © Felix Courteau-Boutin All Right Reserved

#include "InteractableComponent.h"
#include "GameFramework/Actor.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DisplayName = FText::FromString(TEXT("Interactable"));
	DefaultPrompt = FText::FromString(TEXT("Interact"));
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractableComponent::OnInteract_Implementation(AActor* InstigatorActor, AController* InstigatorController)
{
	// Minimal implementation just broadcasts delegate.
	//OnInteraction.Broadcast(this, InstigatorActor, InstigatorController);
}

void UInteractableComponent::OnFocusBegin_Implementation(AActor* InstigatorActor, AController* InstigatorController)
{
	OnFocusBeginEvent.Broadcast(this, InstigatorActor, InstigatorController);
}

void UInteractableComponent::OnFocusEnd_Implementation(AActor* InstigatorActor, AController* InstigatorController)
{
	OnFocusEndEvent.Broadcast(this, InstigatorActor, InstigatorController);
}

FText UInteractableComponent::GetInteractionName_Implementation() const
{
	return DisplayName;
}

FText UInteractableComponent::GetInteractionPrompt_Implementation() const
{
	return DefaultPrompt;
}

void UInteractableComponent::PerformInteraction(AActor* InstigatorActor, AController* InstigatorController)
{
	if (!bIsEnabled || !GetOwner())
	{
		return;
	}

	OnInteraction.Broadcast(this, InstigatorActor, InstigatorController);
}
