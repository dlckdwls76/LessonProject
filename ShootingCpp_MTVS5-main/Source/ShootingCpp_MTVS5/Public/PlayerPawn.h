// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// 전방선언
class UBoxComponent;

UCLASS()
class SHOOTINGCPP_MTVS5_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UBoxComponent> BoxComp;
	
	// 외형
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	// 총구
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UArrowComponent> FirePointComp;
	
	
	// 입력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputMappingContext> IMC_Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputAction> IA_PlayerMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UInputAction> IA_PlayerFire;
	
	UFUNCTION()
	void OnMyMove(const struct FInputActionValue& value);
	
	// 이동하고싶다. 필요요소 : 방향, 크기
	FVector Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	float Speed = 500.f;
	
	// 마우스 왼쪽 버튼을 누르면 총알공장에서 총알을 생성해서 총구에 배치하고싶다.
	void OnMyFirePressed(const struct FInputActionValue& value);
	void OnMyFireReleased(const struct FInputActionValue& value);
	
	bool bAutoFire;
	float CurTime;
	float FireTime = 0.25f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TSubclassOf<class ABulletActor> BulletFactory;
	
	void MakeBullet();
	
	// 총알 발사 소리를 출력하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class USoundBase> FireSound;
	
	int32 CurHP;
	int32 MaxHP = 3;
	
	// 적이 주인공과 부딪히면 호출될 함수
	void OnMyTakeDamage(int32 damage = 1);
	
	
	// 체력이 0이되면 게임오버 UI를 생성해서 화면에 보이게하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TSubclassOf<class UGameOverUI> GameOverUIFactory;
	
	UPROPERTY()
	TObjectPtr<UGameOverUI> GameOverUI;
	
	// 태어나면서 배경 액터를 찾아서 그 머티리얼을 Dynamic으로 기억하고싶다.
	// 살아가면서 배경의 스크롤처리를 하고싶다.
	float ScrollTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	float ScrollSpeed = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<UMaterialInstanceDynamic> DMaterial;
	
};
