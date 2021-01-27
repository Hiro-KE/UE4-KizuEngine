// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/KCombatFunctionLibrary.h"
#include "Engine/Engine.h"
#include "KizuEngine.h"
#include "Core/KCharacter.h"
#include "Core/Combat/KBuff.h"
#include "Core/Combat/KSpawnableAbility.h"
#include "Kismet/GameplayStatics.h"

AKBuff* UKCombatFunctionLibrary::SpawnBuff(AActor* OwnerActor, AActor* TargetActor, TSubclassOf<AKBuff> BuffToSpawn, const FTransform Transform)
{
	if (OwnerActor && TargetActor) {
		if (UWorld* World = OwnerActor->GetWorld()) {
			AKBuff* NewBuff = World->SpawnActorDeferred<AKBuff>(BuffToSpawn, Transform, OwnerActor, Cast<APawn>(OwnerActor));
			if (NewBuff) {
				NewBuff->ServerSetOwnerActor(OwnerActor);
				NewBuff->ServerSetTargetActor(TargetActor);
				UGameplayStatics::FinishSpawningActor(NewBuff, NewBuff->GetTransform());
				return NewBuff;
			}
		}
	}
	else UE_LOG(LogKizu, Warning, TEXT("Unable to spawn the Buff due to invalid Owner or Target."));
	return nullptr;
}

AKSpawnableAbility* UKCombatFunctionLibrary::SpawnSpawnableAbility(AActor* OwnerActor, TSubclassOf<AKSpawnableAbility> SpawnableAbilityToSpawn, FSpawnableAbilitySpawnParams SpawnParams)
{
	if (OwnerActor->IsValidLowLevel()) {
		if (UWorld* World = OwnerActor->GetWorld()) {
			AKSpawnableAbility* SpawnableAbility = World->SpawnActorDeferred<AKSpawnableAbility>(SpawnableAbilityToSpawn, SpawnParams.Transform, OwnerActor, Cast<APawn>(OwnerActor));
			if (SpawnableAbility->IsValidLowLevel()) {
				SpawnableAbility->ServerSetOwner(OwnerActor);
				UGameplayStatics::FinishSpawningActor(SpawnableAbility, SpawnableAbility->GetTransform());
				if (SpawnParams.bInitizalizeMobility) {
					SpawnableAbility->ServerInitializeMovement(SpawnParams.InitialDirection, SpawnParams.TargetActor);
				}
				return SpawnableAbility;
			}
		}
	}
	return nullptr;
}

bool UKCombatFunctionLibrary::IsSameFaction(AKCharacter* CharacterOne, AKCharacter* CharacterTwo)
{
	return CharacterOne->CharacterData.Faction == CharacterTwo->CharacterData.Faction;
}

bool UKCombatFunctionLibrary::IsSameFactionWithCast(AKCharacter* CharacterOne, AActor* CharacterTwo)
{
	if (AKCharacter* KCharacterTwo = Cast<AKCharacter>(CharacterTwo)) {
		return CharacterOne->CharacterData.Faction == KCharacterTwo->CharacterData.Faction;
	}
	return false;
}
