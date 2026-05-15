// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUI.h"

#include "Components/Image.h"
#include "TPS_MTVS5th/TPS_MTVS5th.h"


void UWeaponUI::ShowImage(EWeaponType type, EZoomType zoom)
{
	
	//만약 총의 타입이 gun이면 모두 보이지않게 하고싶다.
	//그렇지 않고 zoom이 ZOOM_OUT이면 크로스헤어, 그렇지않으면 Scope

		
	if (type == EWeaponType::GUN)
	{
		ImageCrosshair->SetVisibility(ESlateVisibility::Hidden);
		ImageScope->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	

	bool bShowCrosshair = (zoom == EZoomType::ZOOM_OUT);
	
	ImageCrosshair->SetVisibility(bShowCrosshair ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	ImageScope->SetVisibility(bShowCrosshair ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}
