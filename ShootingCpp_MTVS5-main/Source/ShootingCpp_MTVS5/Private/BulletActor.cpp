// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "EnemyActor.h"
#include "NiagaraFunctionLibrary.h"
#include "ShootingGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 충돌체를 만들어서 루트로 하고 싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(50.f));
	
	SetRootComponent(BoxComp);
	// 외형을 만들어서 루트에 붙이고 싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
	
	// Mesh의 충돌설정을 끄고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Box의  충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnMyCompBeginOverlap);
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 앞방향으로 계속 이동하고싶다.
	// P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector v = GetActorForwardVector() * Speed;
	SetActorLocation(p0 + v * DeltaTime);
	
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	// // 니가 애너미라면 너죽고
	// if (Cast<AEnemyActor>(OtherActor))
	// {
	// 	OtherActor->Destroy();
	// 	// 나죽자
	// 	this->Destroy();
	// }
}

void ABulletActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 니가 애너미라면 너죽고
	//if (OtherActor->IsA<AEnemyActor>())
	if (auto* enemy = Cast<AEnemyActor>(OtherActor))
	{
		// 니가 적이라면 너죽고
		bool isDead = enemy->OnMyTakeDamage(1);
		if (isDead)
		{
			// 게임모드에게 점수를 1점 획득하라고 하고 싶다.
			auto* gm = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
			gm->AddScore();
		
			// 이곳에서 폭발음을 출력하고싶다.
			UGameplayStatics::PlaySound2D(GetWorld(), ExplosionSound);
		
			// 폭발 VFX를 출력하고싶다.
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionVFX, OtherActor->GetActorLocation());
		}
		
		// 나죽자
		this->Destroy();
		
	}
}
