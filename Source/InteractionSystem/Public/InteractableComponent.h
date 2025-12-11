// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "InteractionTypes.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionEvent, UInteractableComponent*, Interactable, AActor*, InstigatorActor);

UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent 
	: public UActorComponent
	, public IInteractable
{
	GENERATED_BODY()

public:
	UInteractableComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Is this interactable currently enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsEnabled = true;

	/** Simple radius used for overlap-based systems (optional). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRadius = 150.f;

	/** Base display name for UI. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText DisplayName;

	/** Base prompt text, e.g. "Interact", "Open", "Talk". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText DefaultPrompt;

	/** Basic interaction type (instant / hold / etc.). Minimal version doesn’t implement hold logic. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractionType InteractionType = EInteractionType::Instant;

	/** Fired when interaction is performed. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnInteraction;

	/** Fired when scanner begins focusing this interactable. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnFocusBeginEvent;

	/** Fired when scanner stops focusing this interactable. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnFocusEndEvent;

public:
	// IInteractable implementation
	virtual void OnInteract_Implementation(AActor* InstigatorActor) override;
	virtual void OnFocusBegin_Implementation(AActor* InstigatorActor) override;
	virtual void OnFocusEnd_Implementation(AActor* InstigatorActor) override;
	virtual FText GetInteractionName_Implementation() const override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	/** Called by scanners / gameplay code to trigger interaction. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void PerformInteraction(AActor* InstigatorActor);

	/** Enable/Disable at runtime. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionEnabled(bool bNewEnabled) { bIsEnabled = bNewEnabled; }
};

