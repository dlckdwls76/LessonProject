// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPUI.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class TPS_MTVS5TH_API UEnemyHPUI : public UUserWidget
{
	GENERATED_BODY()


	public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr< UProgressBar> HPBar;

	void UpdateHPBar(float cur, float max);
	
};
