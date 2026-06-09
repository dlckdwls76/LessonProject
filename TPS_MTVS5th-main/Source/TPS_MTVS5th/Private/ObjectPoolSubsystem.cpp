// Fill out your copyright notice in the Description page of Project Settings.
#include "ObjectPoolSubsystem.h"

void UObjectPoolSubsystem::InitPool(TSubclassOf<AActor> factory, int32 initSize)
{
	if (nullptr == factory || 0 == initSize)
	{
		return;
	}
	for (int32 i = 0; i < initSize; i++)
	{
		if (AActor* actor = GetWorld()->SpawnActor<AActor>(factory, FVector::ZeroVector, 
			FRotator::ZeroRotator))
		{
			ReturnToPool(actor);
			
		}
	}
}

std::nullptr_t UObjectPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> factory, FVector location, FRotator rotation)
{
	if (nullptr == factory) return nullptr;
	
	AActor* retActor = nullptr;
	
	//ObjectPools에 factory가 있는지? 값이 존재하는지?
	if (ObjectPools.Contains(factory) && ObjectPools[factory].Num() > 0)
		{
		retActor = ObjectPools[factory].Pop();
		}
	else
	{
		//풀이 비어있으면 새로 생성해서 반환
		retActor = GetWorld()->SpawnActor<AActor>(factory,FVector::ZeroVector, FVector::ZeroRotator);
	}
	//초기화 처리
	SetActive(retActor,true);
		
	return retActor;		
}

AActor* UObjectPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> factory, FTransform t)
{
	return SpawnFromPool(factory,t.GetLocation(),t.GetRotation().Rotator());
}

void UObjectPoolSubsystem::ReturnToPool(AActor* actor)
{
	if (nullptr == actor) return;
	//기존에 풀로 관리한것만 넣겠다
	// if (ObjectPools.Contains(actor->GetClass()))
	// {
	// 	SetActive(actor,false);
	// 	TArray<AActor*> array = ObjectPools.Add(actor->GetClass());
	// 	array.Add(actor);
	// }
	SetActive(actor,false);
	ObjectPools.FindOrAdd(actor->GetClass()).Add(actor);
	
}

void UObjectPoolSubsystem::SetActive(AActor* actor, bool bActive)
{
	// 틱처리
	actor->SetActorTickEnabled(bActive);
	// 그리기 처리
	actor->SetActorHiddenInGame(!bActive);
	// 충돌 처리
	actor->SetActorEnableCollision(bActive);
}

void UObjectPoolSubsystem::Deinitialize()
{
	ObjectPools.Empty();
	
	Super::Deinitialize();
}
