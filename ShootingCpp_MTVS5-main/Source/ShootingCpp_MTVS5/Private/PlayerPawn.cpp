// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "BulletActor.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameOverUI.h"
#include "InputActionValue.h"
#include "ShootingGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	
	// 총구를 생성해서
	FirePointComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePointComp"));
	// 루트에 붙이고싶다.
	FirePointComp->SetupAttachment(RootComponent);
	FirePointComp->SetRelativeLocationAndRotation(FVector(0, 0, 100.f), FRotator(90, 0, 0));


	// Mesh의 충돌설정을 끄고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Box의  충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Player"));
	// BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	// BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	auto* pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys)
		{
			subsys->RemoveMappingContext(IMC_Player);
			subsys->AddMappingContext(IMC_Player, 0);
		}
		// 태어날 때 인풋모드를 GameOnly로 하고싶다. 마우스 커서를 안보이게 하고싶다.
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
	}

	
	CurHP = MaxHP;
	auto* gm = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
	gm->SetHP(CurHP, MaxHP);
	
	
	// 1. 태어나면서 배경 액터를 찾아서
	AActor* bg = nullptr;
	for (TActorIterator<AActor> It(GetWorld(), AStaticMeshActor::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (IsValid(Actor) && Actor->ActorHasTag(TEXT("Background")))
		{
			bg = Actor;
			break;
		}
	}
	if (bg)
	{
		auto* mesh = Cast<UStaticMeshComponent>(bg->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		
		// 2. 그 머티리얼을 Dynamic으로 기억하고싶다.
		DMaterial = mesh->CreateDynamicMaterialInstance(0); 
	}
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// DMaterial이 존재하면 ScrollTime을 증가시키고싶다.
	if (DMaterial)
	{
		ScrollTime += DeltaTime * ScrollSpeed;
		DMaterial->SetScalarParameterValue(TEXT("ScrollTime"), ScrollTime);
	}
	
	// 만약 자동 총쏘기가 활성화 되었다면
	if (bAutoFire)
	{
		// 시간이 흐르다가
		CurTime += DeltaTime;
		// 현재시간이 발사시간이 되면
		if (CurTime > FireTime)
		{
			CurTime = 0;
			// 총알을 생성하고싶다.
			MakeBullet();
		}
	}
	
	// P = P0 + vt
	FVector p0 = GetActorLocation();
	//Direction.Normalize();
	FVector v = Direction.GetSafeNormal() * Speed;
	SetActorLocation(p0 + v * DeltaTime);
	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(IA_PlayerMove, ETriggerEvent::Triggered, this, &APlayerPawn::OnMyMove);
		
		input->BindAction(IA_PlayerFire, ETriggerEvent::Started, this, &APlayerPawn::OnMyFirePressed);
		input->BindAction(IA_PlayerFire, ETriggerEvent::Completed, this, &APlayerPawn::OnMyFireReleased);
	}
}

void APlayerPawn::OnMyMove(const FInputActionValue& value)
{
	FVector2D v = value.Get<FVector2D>();
	Direction.Y = v.Y;
	Direction.Z = v.X;
}

void APlayerPawn::OnMyFirePressed(const struct FInputActionValue& value)
{
	MakeBullet();
	bAutoFire = true;
}

void APlayerPawn::OnMyFireReleased(const struct FInputActionValue& value)
{
	bAutoFire = false;
	CurTime = 0;
}

void APlayerPawn::MakeBullet()
{
	FTransform t = FirePointComp->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, t);
	
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

void APlayerPawn::OnMyTakeDamage(int32 damage)
{
	// 체력을 damage만큼 감소하고싶다.
	CurHP -= damage;
	// 게임모드에게 나의 체력을 그려달라고 요청하고싶다.
	auto* gm = Cast<AShootingGameMode>(GetWorld()->GetAuthGameMode());
	gm->SetHP(CurHP, MaxHP);
	// 만약 내 체력이 0 이하가 되면 일시정지 하고싶다.
	if (CurHP <= 0)
	{
		// 게임오버 UI를 화면에 그리고싶다.
		check(GameOverUIFactory);
		GameOverUI = CastChecked<UGameOverUI>(CreateWidget(GetWorld(), GameOverUIFactory));
		GameOverUI->AddToViewport();
		
		auto* pc = GetWorld()->GetFirstPlayerController();
		pc->SetPause(true);
		// 인풋모드를 UIOnly로 하고싶다. 마우스 커서를 보이게 하고싶다.
		pc->SetInputMode(FInputModeUIOnly());
		pc->SetShowMouseCursor(true);
	}
}

