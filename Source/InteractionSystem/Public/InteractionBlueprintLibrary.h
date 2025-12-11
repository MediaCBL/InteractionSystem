// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InteractionTypes.h"
#include "InteractionBlueprintLibrary.generated.h"

class UInteractableComponent;
/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API UInteractionBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Find the first interactable component on an actor (helper for BP). */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	static UInteractableComponent* GetFirstInteractableComponent(AActor* Actor);

	/** Compare two interaction results by distance (for sorting). */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	static bool IsCloserInteraction(const FInteractionResult& A, const FInteractionResult& B);
};
