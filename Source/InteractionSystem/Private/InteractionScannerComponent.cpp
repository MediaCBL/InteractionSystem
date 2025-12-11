// © Felix Courteau-Boutin All Right Reserved

#include "InteractionScannerComponent.h"
#include "InteractableComponent.h"
#include "Interactable.h"
#include "InteractionSource.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

UInteractionScannerComponent::UInteractionScannerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionScannerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionScannerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bScanEnabled)
	{
		UpdateScan(DeltaTime);
	}
}

void UInteractionScannerComponent::UpdateScan(float /*DeltaTime*/)
{
	FHitResult Hit;
	if (PerformLineTrace(Hit))
	{
		HandleNewHit(Hit);
	}
	else
	{
		if (CurrentInteractable)
		{
			ClearCurrentTarget(GetOwner());
		}
	}
}

bool UInteractionScannerComponent::PerformLineTrace(FHitResult& OutHit) const
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return false;
	}

	FVector Start = OwnerActor->GetActorLocation();
	FVector Direction = OwnerActor->GetActorForwardVector();

	// If owner implements IInteractionSource, ask it for view location/direction.
	if (OwnerActor->GetClass()->ImplementsInterface(UInteractionSource::StaticClass()))
	{
		const FVector CustomLoc = IInteractionSource::Execute_GetInteractionViewLocation(OwnerActor);
		const FVector CustomDir = IInteractionSource::Execute_GetInteractionViewDirection(OwnerActor);
		if (!CustomLoc.IsNearlyZero())
		{
			Start = CustomLoc;
		}
		if (!CustomDir.IsNearlyZero())
		{
			Direction = CustomDir.GetSafeNormal();
		}
	}

	const FVector End = Start + Direction * TraceDistance;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(InteractionTrace), false, OwnerActor);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, TraceChannel, Params);

	if (bDrawDebug)
	{
		const FColor Color = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, Color, false, 0.f, 0, 1.5f);
	}

	return bHit;
}

void UInteractionScannerComponent::HandleNewHit(const FHitResult& Hit)
{
	UInteractableComponent* NewInteractable = nullptr;

	if (Hit.GetActor())
	{
		NewInteractable = Hit.GetActor()->FindComponentByClass<UInteractableComponent>();
	}

	if (!NewInteractable || !NewInteractable->bIsEnabled)
	{
		if (CurrentInteractable)
		{
			ClearCurrentTarget(GetOwner());
		}
		return;
	}

	const float Distance = (Hit.ImpactPoint - Hit.TraceStart).Size();

	if (NewInteractable == CurrentInteractable)
	{
		// Same target, just update distance.
		CurrentResult.Distance = Distance;
		return;
	}

	// Change focus.
	ClearCurrentTarget(GetOwner());
	SetCurrentTarget(NewInteractable, GetOwner(), Distance);
}

void UInteractionScannerComponent::ClearCurrentTarget(AActor* InstigatorActor)
{
	if (CurrentInteractable)
	{
		IInteractable::Execute_OnFocusEnd(CurrentInteractable, InstigatorActor);
		OnFocusChanged.Broadcast(CurrentInteractable, InstigatorActor);
		CurrentInteractable = nullptr;
		CurrentResult = FInteractionResult();
	}
}

void UInteractionScannerComponent::SetCurrentTarget(UInteractableComponent* NewInteractable, AActor* InstigatorActor, float Distance)
{
	CurrentInteractable = NewInteractable;
	CurrentResult.InteractableComponent = NewInteractable;
	CurrentResult.InteractableActor = NewInteractable->GetOwner();
	CurrentResult.Distance = Distance;

	IInteractable::Execute_OnFocusBegin(NewInteractable, InstigatorActor);
	OnFocusChanged.Broadcast(NewInteractable, InstigatorActor);
}

void UInteractionScannerComponent::TryInteract(AActor* InstigatorActor)
{
	if (!CurrentInteractable || !CurrentInteractable->bIsEnabled)
	{
		return;
	}

	CurrentInteractable->PerformInteraction(InstigatorActor);
}


