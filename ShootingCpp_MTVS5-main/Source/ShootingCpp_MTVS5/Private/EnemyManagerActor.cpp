// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "EnemyActor.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 마이루트컴포넌트를 생성해서 루트로 하고싶다.
	MyRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComp"));
	SetRootComponent(MyRootComp);
	// 파이어포인트컴포넌트를 생성해서 마이루트에 붙이고싶다.
	SpawnPointComp = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointComp"));
	SpawnPointComp->SetupAttachment(RootComponent);
	SpawnPointComp->SetRelativeRotation(FRotator(-90, 180, 0));

	// EnemyFactory를 로드해서 채우고싶다.
	ConstructorHelpers::FClassFinder<AEnemyActor> tempEnemyFactory(
		TEXT("/Script/Engine.Blueprint'/Game/Shooting/Blueprints/BP_EnemyActor.BP_EnemyActor_C'"));

	if (tempEnemyFactory.Succeeded())
	{
		EnemyFactory = tempEnemyFactory.Class;
	}
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재시간이 증가하다가
	CurTime += DeltaTime;
	// 현재시간이 생성시간을 초과하면
	if (CurTime > MakeTime)
	{
		MakeEnemy();
		CurTime = 0;
	}
}

void AEnemyManagerActor::MakeEnemy()
{
	// 적을 생성하고 싶다(SpawnPointComp)
	GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, SpawnPointComp->GetComponentTransform());
}
