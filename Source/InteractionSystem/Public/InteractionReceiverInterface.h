#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionReceiverInterface.generated.h"

class UPassiveInteractableComponent;

UINTERFACE(BlueprintType)
class INTERACTIONSYSTEM_API UInteractionReceiverInterface : public UInterface
{
	GENERATED_BODY()
};

class INTERACTIONSYSTEM_API IInteractionReceiverInterface
{
	GENERATED_BODY()

public:
	/**
	 * Called when the receiver enters/exits an interactable zone.
	 *
	 * @param InteractableActor     The actor that owns the PassiveInteractableComponent.
	 * @param InteractableComponent The component that triggered the notification.
	 * @param bIsInZone             true on begin overlap, false on end overlap.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="InteractionSystem|Passive")
	void OnPassiveInteractableZoneChanged(
		AActor* InteractableActor,
		UPassiveInteractableComponent* InteractableComponent,
		bool bIsInZone
	);
};
