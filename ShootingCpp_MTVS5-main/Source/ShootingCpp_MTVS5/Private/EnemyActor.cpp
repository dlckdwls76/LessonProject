// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "EnemyHPUI.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌체를 생성해서 
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50.f));
	
	// 충돌체를 루트로 하고싶다.
	SetRootComponent(BoxComp);
	// 외형을 생성하고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// 외형을 루트에 붙이고싶다.
	MeshComp->SetupAttachment(RootComponent);
	
	
	// 외형의 에셋을 로드해서 외형컴포넌트에 반영하고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(tempMesh.Object); 
	}
	
	
	// 외형의 재질을 로드해서 외형 컴포넌트의 재질에 반영하고싶다.
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (tempMat.Succeeded())
	{
		MeshComp->SetMaterial(0, tempMat.Object);
	}
	
	// Mesh의 충돌설정을 끄고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Box의  충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));
	
	UIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIComp"));
	UIComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	HPUI = Cast<UEnemyHPUI>(UIComp->GetWidget());
	HP = MaxHP;
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnMyCompBeginOverlap);
	
	// 태어날 때 방향을 정하고싶다.
	
	// 나머지 확률로 앞 방향으로
	Direction = GetActorForwardVector();
	
	int32 randValue = FMath::RandRange(0, 9);
	
	// 30%의 확률로 주인공 방향으로,
	if (randValue < 3)
	{
		//UGameplayStatics::GetActorOfClass()
		//APawn* target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		APawn* target = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (target != nullptr && target->IsValidLowLevel())
		{
			Direction = target->GetActorLocation() - this->GetActorLocation();
			Direction.Normalize();
			// 회전방향을 구하고
			FRotator rot = UKismetMathLibrary::MakeRotFromXZ(Direction, GetActorUpVector());
			// 반영하고싶다.
			SetActorRotation(rot);
		}
	}
	 
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 살아가면서 그 방향으로 계속 이동하고싶다.
	// P = P0 + vt
	SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);
}

void AEnemyActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* player = Cast<APlayerPawn>(OtherActor))
	{
		// 주인공에게 데미지를 주고싶다.
		player->OnMyTakeDamage();
		
		// 나죽자
		this->Destroy();
	}
}

int32 AEnemyActor::GetHP()
{
	return CurHP;
}

void AEnemyActor::SetHP(int32 value)
{
	CurHP = value;
	// UI에 반영하고싶다.
	HPUI->UpdateHpBar(CurHP, MaxHP);
}

bool AEnemyActor::OnMyTakeDamage(int32 damage)
{
	HP -= damage;
	bool bDead = HP <= 0;
	if (bDead)
		Destroy();
	return bDead;
}

