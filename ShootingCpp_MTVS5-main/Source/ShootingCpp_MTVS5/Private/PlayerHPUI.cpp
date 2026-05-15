// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHPUI::UpdateHP(int32 cur, int32 max)
{
	float per = static_cast<float>(cur) / max;
	
	per = FMath::Clamp(per, 0.f, 1.f);
	
	HPBar->SetPercent(per);
	
	FString hpPer = FString::Printf(TEXT("%d %%"), static_cast<int32>(per * 100));
	
	TextHPPer->SetText(FText::FromString(hpPer));
}
