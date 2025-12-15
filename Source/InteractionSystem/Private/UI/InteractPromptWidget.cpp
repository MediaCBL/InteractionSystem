// © Felix Courteau-Boutin All Right Reserved

#include "UI/InteractPromptWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInteractPromptWidget::SetPromptText(const FText& InText)
{
	if (PromptText)
	{
		PromptText->SetText(InText);
	}
}

void UInteractPromptWidget::SetKeyIcon(UTexture2D* InTexture)
{
	if (KeyImage && InTexture)
	{
		KeyImage->SetBrushFromTexture(InTexture);
	}
}
