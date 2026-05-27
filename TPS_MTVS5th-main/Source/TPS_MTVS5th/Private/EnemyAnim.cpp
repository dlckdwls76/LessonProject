// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnim.h"
#include "Enemy.h" 
#include "FSMComponent.h"
#include "NavigationSystem.h"

void UEnemyAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 태어날 때 나를 소유한 오너를 기억하고싶다.
	
		
		Enemy = Cast<AEnemy>(TryGetPawnOwner());
	
}

void UEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
//살아가면서 그 오너의 상태와 공격여부를 동기화 하고싶다.

	if (Enemy && Enemy -> IsValidLowLevel() && Enemy->FSMComp && Enemy->FSMComp -> IsValidLowLevel())
		{
		State = Enemy ->FSMComp ->State;
		bAttack = Enemy ->FSMComp->bAttack;
	}
}

void UEnemyAnim::AnimNotify_AttackEnd()
{
	PRINT_LOG(TEXT("AnimNotify_AttackEnd"));
	
	if (Enemy && Enemy -> IsValidLowLevel() && Enemy->FSMComp && Enemy->FSMComp -> IsValidLowLevel())
	{
		Enemy->FSMComp->OnMyAttackEnd();
	}	
}

void UEnemyAnim::AnimNotify_Hit()
{
	
	if (Enemy&& Enemy -> IsValidLowLevel() && Enemy ->FSMComp && Enemy->FSMComp -> IsValidLowLevel())
	{
		Enemy ->FSMComp->bAttack = false;
	}
	//PRINT_LOG(TEXT("AnimNotify_Hit"));
	//주인공에게 데미지를 가하고싶다.
}

void UEnemyAnim::AnimNotify_DamageEnd()
{
	Montage_Stop(0,EnemyMontage);
}

void UEnemyAnim::AnimNotify_DieEnd()
{
	
}

void UEnemyAnim::PlayDamgeMontage(int32 idx)
{
	FString sectionName = FString::Printf(TEXT("Damage%d"),idx);

	//Enemy->PlayAnimMontage(EnemyMontage, 0 , SectionName);
	
	Montage_Play(EnemyMontage);
	Montage_JumpToSection(FName(*sectionName), EnemyMontage);
}

void UEnemyAnim::PlayDieMontage()
{
FString sectionName = TEXT("Die");

//Enemy->PlayAnimMontage(EnemyMontage, 0 , FName(*sectionName));
	
Montage_Play(EnemyMontage);
Montage_JumpToSection(FName(*sectionName), EnemyMontage);

}

