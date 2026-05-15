// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHPUI.h"

#include "Components/ProgressBar.h"

void UEnemyHPUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// Back의 Percent가 Front의 Percent를 따라가게 하고싶다.
	float f = FMath::Lerp(HPBarBack->GetPercent(), HPBarFront->GetPercent(), InDeltaTime * 15);
	
	HPBarBack->SetPercent(f);
}

void UEnemyHPUI::UpdateHpBar(int32 cur, int32 max)
{
	HPBarFront->SetPercent((float)cur/max);
}
