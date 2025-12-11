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

void UInteractableComponent::OnInteract_Implementation(AActor* InstigatorActor)
{
	// Minimal implementation just broadcasts delegate.
	OnInteraction.Broadcast(this, InstigatorActor);
}

void UInteractableComponent::OnFocusBegin_Implementation(AActor* InstigatorActor)
{
	OnFocusBeginEvent.Broadcast(this, InstigatorActor);
}

void UInteractableComponent::OnFocusEnd_Implementation(AActor* InstigatorActor)
{
	OnFocusEndEvent.Broadcast(this, InstigatorActor);
}

FText UInteractableComponent::GetInteractionName_Implementation() const
{
	return DisplayName;
}

FText UInteractableComponent::GetInteractionPrompt_Implementation() const
{
	return DefaultPrompt;
}

void UInteractableComponent::PerformInteraction(AActor* InstigatorActor)
{
	if (!bIsEnabled || !GetOwner())
	{
		return;
	}

	OnInteract(InstigatorActor); // Calls the BlueprintNativeEvent implementation.
}
