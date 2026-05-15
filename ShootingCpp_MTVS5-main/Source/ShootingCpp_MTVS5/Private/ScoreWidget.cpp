// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(int32 newScore)
{
	// newSocre를 TextScore에 표시하고싶다.
	TextScore->SetText(FText::AsNumber(newScore));
}

void UScoreWidget::UpdateHighScore(int32 newHighScore)
{
	TextHighScore->SetText(FText::AsNumber(newHighScore));
}
