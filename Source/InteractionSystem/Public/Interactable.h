// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Minimal generic interface for anything that can be interacted with.
 * Implemented by components (preferred) or actors.
 */
class INTERACTIONSYSTEM_API IInteractable
{
	GENERATED_BODY()

public:
	/** Called when an interaction is triggered. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* InstigatorActor);

	/** Optional: called when a scanner starts focusing this interactable. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnFocusBegin(AActor* InstigatorActor);

	/** Optional: called when a scanner stops focusing this interactable. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnFocusEnd(AActor* InstigatorActor);

	/** Display name used in prompts – override for dynamic naming. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionName() const;

	/** Prompt text like “Press E to Open” – override per actor if needed. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionPrompt() const;
};
