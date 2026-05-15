// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"

#include "Components/BoxComponent.h"


// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌체를 생성해서 루트로 하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	// 충돌체의 BoxExtents를 50으로 하고싶다.
	BoxComp->SetBoxExtent(FVector(50.f));
	
	// 외형을 생성해서 루트에 붙이고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
	// 충돌 설정을 하고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("DestroyZone"));
}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestroyZoneActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	// 너죽어
	OtherActor->Destroy();
}

