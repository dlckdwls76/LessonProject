// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"

#include "MySaveGameHighScore.h"
#include "PlayerHPUI.h"
#include "ScoreWidget.h"
#include "Kismet/GameplayStatics.h"

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ScoreUIFactory를 이용해서 ScoreUI를 생성하고 Viewport에 붙이고싶다.
	check(ScoreUIFactory);
	if (ScoreUIFactory)
	{
		ScoreUI = Cast<UScoreWidget>(CreateWidget(GetWorld(), ScoreUIFactory));
		if (ScoreUI)
		{
			ScoreUI->AddToViewport();
		}
	}

	if (PlayerHPUIFactory)
	{
		PlayerHPUI = Cast<UPlayerHPUI>(CreateWidget(GetWorld(), PlayerHPUIFactory));
		PlayerHPUI->AddToViewport();
	}
	
	MyGameLoad();
}

void AShootingGameMode::AddScore(int32 point)
{
	// 점수를 증가
	Score += point;
	// 점수UI에 반영
	ScoreUI->UpdateScore(Score);
	
	// 만약 현재점수가 최고점수보다 커지면
	if (Score > HighScore)
	{
		// 최고점수를 현재점수로 갱신하고싶다.
		HIGH_SCORE = Score;
		MyGameSave();
	}
}

void AShootingGameMode::MyGameSave()
{
	// SaveGame 객체를 생성하고싶다.
	auto* sgInst = UGameplayStatics::CreateSaveGameObject(UMySaveGameHighScore::StaticClass());
	auto* mySaveInst = Cast<UMySaveGameHighScore>(sgInst);
	
	// 생성된 객체의 내용을 채우고싶다.
	mySaveInst->HighScore_Save = HIGH_SCORE;
	
	// 생성된 객체를 슬롯에 저장하고싶다.
	UGameplayStatics::SaveGameToSlot(mySaveInst, SlotName, 0);
}

void AShootingGameMode::MyGameLoad()
{
	// 파일이 존재하는가?
	if (false == UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		HIGH_SCORE = 0;
		return;
	}
	
	// 파일을 읽고
	auto* sg = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	auto* mySaveInst = Cast<UMySaveGameHighScore>(sg);
	// 내용을 끄집어내고싶다.
	HIGH_SCORE = mySaveInst->HighScore_Save;
}

void AShootingGameMode::SetHighScore(int32 newScore)
{
	HighScore = newScore;
	ScoreUI->UpdateHighScore(HighScore);
}

int32 AShootingGameMode::GetHighScore()
{
	return HighScore;
}

void AShootingGameMode::SetHP(int32 cur, int32 max)
{
	PlayerHPUI->UpdateHP(cur, max);
}
