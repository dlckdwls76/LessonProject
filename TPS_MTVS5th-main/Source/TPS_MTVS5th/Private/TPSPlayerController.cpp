// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

#include "WeaponUI.h"
#include "Blueprint/UserWidget.h"
#include "TPS_MTVS5th/TPS_MTVS5th.h"


void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponUI = CreateWidget<UWeaponUI>(this, WeaponUIFactory, "WeaponUI");
	
	if (!IsValid(WeaponUI))
	{
		UE_LOG(LogTemp, Error, TEXT("ATPSPlayerController: (BeginPlay) Failed Weapon Ui CreateWidget."));
	}
	
	if (IsValid(WeaponUI)) 
	{
		WeaponUI->AddToViewport();
	}

}

void ATPSPlayerController::SetWeaponImage(EWeaponType type, EZoomType zoom)
{

	if (IsValid(WeaponUI)) 
	{
		WeaponUI->ShowImage(type, zoom);
	}
}
