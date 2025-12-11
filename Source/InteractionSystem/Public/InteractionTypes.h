#pragma once

#include "CoreMinimal.h"
#include "InteractionTypes.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Instant     UMETA(DisplayName = "Instant"),
	Hold        UMETA(DisplayName = "Hold"),
	Toggle      UMETA(DisplayName = "Toggle"),
	Continuous  UMETA(DisplayName = "Continuous")
};

USTRUCT(BlueprintType)
struct FInteractionResult
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	class UActorComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AActor* InteractableActor = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float Distance = 0.f;

	bool IsValid() const { return InteractableComponent != nullptr && InteractableActor != nullptr; }
};
