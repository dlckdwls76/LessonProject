// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TextScore; 
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> TextHighScore; 
	
	// 점수가 갱신되면 화면에 그리는 기능
	void UpdateScore(int32 newScore);
	
	void UpdateHighScore(int32 newHighScore);
};
