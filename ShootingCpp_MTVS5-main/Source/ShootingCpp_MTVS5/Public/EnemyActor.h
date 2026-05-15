// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_MTVS5_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 만약 주인공과 부딪히면 너죽고 나죽고 하고싶다.
	UFUNCTION()
	void OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// 충돌체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UBoxComponent> BoxComp;
	
	// 외형
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	
	// 태어날 때 방향을 정하고싶다.
	// 30%의 확률로 주인공 방향으로,
	// 나머지 확률로 앞 방향으로 
	
	// 살아가면서 그 방향으로 계속 이동하고싶다.
	
	// 방향, 크기
	FVector Direction;
	float Speed = 500.f;
	
	// 체력을 만들고 태어날 때 체력이 꽉 차게 하고싶다.
	int32 CurHP;
	int32 MaxHP = 2;
	
	_declspec(property(put=SetHP, get=GetHP)) int32 HP;
	int32 GetHP();
	void SetHP(int32 value);
	
	// 체력 UI를 생성하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UWidgetComponent> UIComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVar")
	TObjectPtr<class UEnemyHPUI> HPUI;
	
	bool OnMyTakeDamage(int32 damage);

};
