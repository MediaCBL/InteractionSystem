// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponentBase.h"
#include "PassiveInteractableComponent.generated.h"

class UWidgetComponent;
class UShapeComponent;

UCLASS(ClassGroup=(InteractionSystem), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UPassiveInteractableComponent : public UInteractableComponentBase
{
	GENERATED_BODY()

public:
	UPassiveInteractableComponent();

	UShapeComponent* GetTrigger() const { return TriggerComponent; }

protected:
	virtual void BeginPlay() override;

	void NotifyReceiver(AActor* OtherActor, bool bIsInZone);

	/** Called by derived classes to bind overlap */
	void BindOverlapEvents();
		
	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintCallable)
	void HandleEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void ShowPrompt(bool bShow);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactable")
	TObjectPtr<UShapeComponent> TriggerComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
	UWidgetComponent* PromptWidgetComponent;

private:

	void SetTriggerComponentReference();
};

