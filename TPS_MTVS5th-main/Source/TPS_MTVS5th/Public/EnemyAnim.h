// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPS_MTVS5th/TPS_MTVS5th.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */	
UCLASS()
class TPS_MTVS5TH_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	// 태어날 때 나를 소유한 오너를 기억하고싶다.
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = FSM)
	TObjectPtr<class AEnemy> Enemy;
    
	// 상태
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = FSM)
	EEnemyState State;
    
	// 공격
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bAttack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	class UAnimMontage* EnemyMontage;

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Hit();
	
	UFUNCTION()
	void AnimNotify_DamageEnd();
	
	UFUNCTION()
	void AnimNotify_DieEnd();
	
	void PlayDamgeMontage(int32 idx);
	void PlayDieMontage();

};
