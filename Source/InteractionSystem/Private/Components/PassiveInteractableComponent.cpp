// © Felix Courteau-Boutin All Right Reserved

#include "Components/PassiveInteractableComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Pawn.h"
#include "InteractionReceiverInterface.h"
#include "Components/WidgetComponent.h"
#include "Components/Colliders/InteractionColliderInterface.h"

UPassiveInteractableComponent::UPassiveInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPassiveInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!TriggerComponent)
	{
		SetTriggerComponentReference();
	}

	if (!PromptWidgetComponent)
	{
		PromptWidgetComponent = GetOwner()->FindComponentByClass<UWidgetComponent>();
	}

	BindOverlapEvents();
}

void UPassiveInteractableComponent::BindOverlapEvents()
{
	if (!TriggerComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PassiveInteractableComponent has no TriggerComponent"));
		return;
	}

	TriggerComponent->SetGenerateOverlapEvents(true);
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(
		this, &UPassiveInteractableComponent::HandleBeginOverlap);

	TriggerComponent->OnComponentEndOverlap.AddDynamic(
		this, &UPassiveInteractableComponent::HandleEndOverlap);
}

void UPassiveInteractableComponent::HandleBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ShowPrompt(true);
	NotifyReceiver(OtherActor, true);
}

void UPassiveInteractableComponent::HandleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ShowPrompt(false);
	NotifyReceiver(OtherActor, false);
}

void UPassiveInteractableComponent::NotifyReceiver(AActor* OtherActor, bool bIsInZone)
{
	if (!OtherActor)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn || !Pawn->IsPlayerControlled())
	{
		return;
	}

	AActor* Receiver = Pawn;

	if (!Receiver->GetClass()->ImplementsInterface(UInteractionReceiverInterface::StaticClass()))
	{
		if (AController* Controller = Pawn->GetController())
		{
			Receiver = Controller;
		}
	}

	if (Receiver && Receiver->GetClass()->ImplementsInterface(UInteractionReceiverInterface::StaticClass()))
	{
		IInteractionReceiverInterface::Execute_OnPassiveInteractableZoneChanged(
			Receiver,
			GetOwner(),
			this,
			bIsInZone
		);
	}
}

void UPassiveInteractableComponent::ShowPrompt(bool bShow)
{
	if (!PromptWidgetComponent) return;
	PromptWidgetComponent->SetVisibility(bShow);
}

void UPassiveInteractableComponent::SetTriggerComponentReference()
{
	UShapeComponent* FoundCollider = nullptr;

	TArray<UActorComponent*> Components;
	GetOwner()->GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!Comp)
		{
			continue;
		}

		if (Comp->GetClass()->ImplementsInterface(UInteractionColliderInterface::StaticClass()))
		{
			FoundCollider = Cast<UShapeComponent>(Comp);
			break;
		}
	}

	TriggerComponent = FoundCollider;
}
