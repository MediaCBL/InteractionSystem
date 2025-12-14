// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "InteractionTypes.h"
#include "Components/InteractableComponentBase.h"
#include "InteractableComponent.generated.h"

UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent 
	: public UInteractableComponentBase
	, public IInteractable
{
	GENERATED_BODY()

public:
	UInteractableComponent();

protected:
	virtual void BeginPlay() override;

public:

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

	/** Fired when scanner begins focusing this interactable. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnFocusBeginEvent;

	/** Fired when scanner stops focusing this interactable. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnFocusEndEvent;

public:
	// IInteractable implementation
	void OnInteract_Implementation(AActor* InstigatorActor, AController* InstigatorController);
	virtual void OnFocusBegin_Implementation(AActor* InstigatorActor, AController* InstigatorController) override;
	virtual void OnFocusEnd_Implementation(AActor* InstigatorActor, AController* InstigatorController) override;
	virtual FText GetInteractionName_Implementation() const override;
	virtual FText GetInteractionPrompt_Implementation() const override;

	/** Enable/Disable at runtime. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionEnabled(bool bNewEnabled) { bIsEnabled = bNewEnabled; }
};

