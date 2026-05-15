// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyZoneActor.generated.h"

UCLASS()
class SHOOTINGCPP_MTVS5_API ADestroyZoneActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestroyZoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	// 충돌체를 생성해서 루트로 하고싶다.
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UBoxComponent> BoxComp;
	// 충돌체의 BoxExtents를 50으로 하고싶다.
	// 외형을 생성해서 루트에 붙이고싶다.
	UPROPERTY(EditAnywhere, Category = MyVar)
	TObjectPtr<class UStaticMeshComponent> MeshComp;
	
};
