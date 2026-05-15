// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API UEnemyHPUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UProgressBar> HPBarBack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UProgressBar> HPBarFront;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void UpdateHpBar(int32 cur, int32 max);
};
