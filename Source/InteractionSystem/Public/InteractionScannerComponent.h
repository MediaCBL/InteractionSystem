// © Felix Courteau-Boutin All Right Reserved
#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/ActorComponent.h"
#include "InteractionTypes.h"
#include "InteractionScannerComponent.generated.h"

class UInteractableComponent;

/**
 * Scans in front of owner (or provided source) and selects best interactable.
 * Minimal version: single trace, one active target, single TryInteract() call.
 */
UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionScannerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionScannerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Whether scanning is enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Scanner")
	bool bScanEnabled = true;

	/** Max distance for line trace. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Scanner")
	float TraceDistance = 500.f;

	/** Collision channel used for traces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Scanner")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/** Whether to draw debug lines. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Debug")
	bool bDrawDebug = false;

	/** Current target result. */
	UPROPERTY(BlueprintReadOnly, Category = "Interaction|Scanner")
	FInteractionResult CurrentResult;

	/** Called when focus changes from one interactable to another (or none). */
	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnInteractionEvent OnFocusChanged;

public:
	/** Attempt to interact with the current target, if any. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void TryInteract(AActor* InstigatorActor, AController* InstigatorController);

protected:
	void UpdateScan(float DeltaTime);
	bool PerformLineTrace(FHitResult& OutHit) const;
	void HandleNewHit(const FHitResult& Hit);
	void ClearCurrentTarget(AActor* InstigatorActor, AController* InstigatorController = nullptr);
	void SetCurrentTarget(UInteractableComponent* NewInteractable, AActor* InstigatorActor, float Distance, AController* InstigatorController = nullptr);

	/** Cached currently focused interactable. */
	UPROPERTY()
	UInteractableComponent* CurrentInteractable = nullptr;
};
