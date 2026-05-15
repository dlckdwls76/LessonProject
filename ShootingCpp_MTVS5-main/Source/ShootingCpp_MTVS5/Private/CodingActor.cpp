// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"

// Sets default values
ACodingActor::ACodingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();
	
	FString str = TEXT("Hello World!");
	
	UE_LOG(LogTemp, Warning, TEXT("string : %s"), *str);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, *str);
	
	int32 number = 10;
	UE_LOG(LogTemp, Warning, TEXT("number : %d"), number);
	
	bool isGood = true;
	UE_LOG(LogTemp, Warning, TEXT("number : %d"), isGood);
	
	float pi = 3.141592f;
	UE_LOG(LogTemp, Warning, TEXT("pi : %.2f"), pi);
	
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACodingActor::MyAdd(int32 a, int32 b)
{
	return a + b;
}

int32 ACodingActor::MyAddNative_Implementation(int32 a, int32 b)
{
	return a + b;
}

