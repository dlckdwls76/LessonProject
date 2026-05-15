// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMangagerActor.h"
#include "EnemyActor.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemyMangagerActor::AEnemyMangagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//마이루트컴포넌트를 생성해서 루트로 하고싶다.
	MyRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComp"));
	MyRootComp->SetupAttachment(RootComponent);
	
	//파이어포인트컴포넌트를 생성해서 마이루트에 붙이고싶다.
	/*SpawnPointComp = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPointComp"));
	SpawnPointComp->SetupAttachment(RootComponent);
	SpawnPointComp->SetRelativeRotation(FRotator(-90.f, 180.f, 0.f));*/
	//Rotation : -90, 180, 0
	
	//EnemyFactory를 로드해서 채우고싶다.
	// ConstructorHelpers::FClassFinder<AEnemyActor>tempEnemyFactory(TEXT("Script/En"))
	//
	// if (tempEnemyFactory.Succeeded())
	// {
	// 	EnemyFactory = tempEnemyFactory.Class;
	// 	
	// 	
	// }
}

// Called when the game starts or when spawned
void AEnemyMangagerActor::BeginPlay()
{
	Super::BeginPlay();
	CurTime = 0.f;
}

// Called every frame
void AEnemyMangagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//현재시간이 증가하다가
	CurTime += DeltaTime * 0.5f;
	//현재시간이 생성시간을 초과히면
	if (CurTime > MakeTime)
	{
		MakeEnemy();
		CurTime = 0.f;
	}
	
}

int SpawnPointComp;

void AEnemyMangagerActor::MakeEnemy()
{
	//적을 생성하고싶다(SpawnPointComp)
	if (EnemyFactory != nullptr)
	{
		// 정상적인 SpawnActor 문법
		GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, SpawnPointComp->GetComponentTransform());
	}
}



