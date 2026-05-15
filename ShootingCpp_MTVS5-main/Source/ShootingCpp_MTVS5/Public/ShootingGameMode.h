// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API AShootingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyVar)
	TSubclassOf<class UScoreWidget> ScoreUIFactory;
	
	UPROPERTY()
	TObjectPtr<UScoreWidget> ScoreUI;
	
	int32 Score;

	// 점수를 획득하는 기능
	void AddScore(int32 point = 1);
	
	void MyGameSave();
	void MyGameLoad();
	
	FString SlotName = TEXT("HighScore");
	
	int32 HighScore;
	_declspec(property(put=SetHighScore, get=GetHighScore)) int32 HIGH_SCORE;
	
	void SetHighScore(int32 newScore);
	
	int32 GetHighScore();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MyVar)
	TSubclassOf<class UPlayerHPUI> PlayerHPUIFactory;
	
	UPROPERTY()
	TObjectPtr<UPlayerHPUI> PlayerHPUI;

	void SetHP(int32 cur, int32 max);

};
