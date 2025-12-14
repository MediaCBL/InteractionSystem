// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInteractionEvent, UInteractableComponentBase*, Interactable, AActor*, InstigatorActor, AController*, InstigatorController);

UCLASS(ClassGroup=(InteractionSystem), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractableComponentBase();
	
	/** Called by scanners / gameplay code to trigger interaction. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void PerformInteraction(AActor* InstigatorActor, AController* InstigatorController);
	
	/** Fired when interaction is performed. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnInteraction;
	
	/** Is this interactable currently enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsEnabled = true;

};
