// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class SHOOTINGCPP_MTVS5_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 일정시간마다 적공장에서 적을 생성해서 스폰위치에 배치하고싶다.
	// 현재시간, 생성시간, 적공장, 스폰컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	TObjectPtr<USceneComponent> MyRootComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	TObjectPtr<class UArrowComponent> SpawnPointComp;	
	
	float CurTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	float MakeTime = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyVar)
	TSubclassOf<class AEnemyActor> EnemyFactory;
	
	// 생성함수
	void MakeEnemy();

};
