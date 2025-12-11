// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionSource.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UInteractionSource : public UInterface
{
	GENERATED_BODY()
};

/**
 * Your Character / PlayerController can implement this if you want more control than just using GetActorLocation().
 */
class INTERACTIONSYSTEM_API IInteractionSource
{
	GENERATED_BODY()

public:
	/** Origin point for traces (camera, eyes, etc.) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FVector GetInteractionViewLocation() const;

	/** Direction for traces (camera forward, etc.) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FVector GetInteractionViewDirection() const;
};
