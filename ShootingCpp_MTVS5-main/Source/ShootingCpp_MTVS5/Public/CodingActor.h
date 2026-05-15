// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingActor.generated.h"

UCLASS()
class SHOOTINGCPP_MTVS5_API ACodingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	
public:
	//Edit / Visible + Anywhere / DefaultsOnly / InstanceOnly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CodingActor)
	int32 Literal = 10;
	
	UFUNCTION(BlueprintCallable)
	int32 MyAdd(int32 a, int32 b);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 MyAddNative(int32 a, int32 b);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int32 MyAddImp(int32 a, int32 b);

};
