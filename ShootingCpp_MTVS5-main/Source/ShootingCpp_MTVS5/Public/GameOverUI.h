// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> ButtonRestart;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

	UFUNCTION()
	void OnMyRestart();
	UFUNCTION()
	void OnMyQuit();
	// 태어날 때 버튼에 이벤트 함수를 연결하고싶다.
	virtual void NativeConstruct() override;
	
	
};
