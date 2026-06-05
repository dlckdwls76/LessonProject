// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "TPS_MTVS5th/TPS_MTVS5th.h"
#include "TPSPlayer.generated.h"

//DECLARE_DELEGATE()
//DECLARE_DYNAMIC_DELEGATE()
//DECLARE_DYNAMIC_MULTICAST_DELEGATE()
//DECLARE_EVENT


DECLARE_MULTICAST_DELEGATE_OneParam(FInputComponentDelegate, class 
	UEnhancedInputComponent*);


UCLASS()
class TPS_MTVS5TH_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();
	void PossessedBy(AController* NewController);

protected:
	void OnMyChooseGun(const FInputActionValue& InputActionValue);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	// 카메라 컴포넌트를 붙이고싶다.
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class USpringArmComponent> CameraBoomComp;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UCameraComponent> CameraComp;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class USkeletalMeshComponent> GunComp;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UStaticMeshComponent> SniperComp;
	
	// 입력에 대한 변수와 함수를 만들고싶다.
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSMove;	

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSLook;	
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSJump;	
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSFire;	

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPS1Key;	

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPS2Key;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSZoom;
	

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSJog;

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSCrouch;

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputAction> IA_TPSDiveRoll;

	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UInputMappingContext> IMC_TPSPlayer;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TSubclassOf<class ABullet> BulletFactory;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<UClass> BulletImpactFactory;
	
	UPROPERTY()
	TObjectPtr<class ATPSPlayerController> PlayerCtrl;
	
	
	// 총쏠때 소리를 내고싶다.
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, Category = MyVar)
	TSubclassOf<UCameraShakeBase> FireCameraShake;
	
	UPROPERTY()
	TObjectPtr<class UPlayerBaseComponent> MoveComp;

	UPROPERTY()
	TObjectPtr<class UPlayerBaseComponent> FireComp;
	
	
	FInputComponentDelegate InputComponentDelegate;	
	

};
