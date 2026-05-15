// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGameHighScore.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_MTVS5_API UMySaveGameHighScore : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 HighScore_Save;
};
