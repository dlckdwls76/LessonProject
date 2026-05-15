// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API UPlayerHPUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UProgressBar> HPBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TextHPPer;
	
	void UpdateHP(int32 cur, int32 max);

};
