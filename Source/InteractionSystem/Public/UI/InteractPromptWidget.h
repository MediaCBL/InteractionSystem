// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractPromptWidget.generated.h"

UCLASS()
class INTERACTIONSYSTEM_API UInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetPromptText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	void SetKeyIcon(UTexture2D* InTexture);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PromptText;

	UPROPERTY(meta = (BindWidget))
	class UImage* KeyImage;
};
