// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/SphereComponent.h"

#include "EnemyCharacter.generated.h"

class APlayerChar; //Refrence to the Player

UCLASS()
class CPPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerChar* PlayerRef;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float Hp;

	UPROPERTY(EditAnywhere)
		float EnemyAttack;

	UPROPERTY(EditAnywhere)
		float EnemyAttackCD;

	UPROPERTY(EditAnywhere)
		float LastTimeEnemyAttack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool IsEnemyAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsEnemyDead;

	UPROPERTY(EditAnywhere)
		UClass* BPProjectile;

	UPROPERTY(EditAnywhere)
		float ProjectilImpulse;

	void Attack(AActor* AttackTarget);

	UPROPERTY(EditAnywhere)
		USphereComponent* EnemySightSphere;

	UPROPERTY(EditAnywhere)
		USphereComponent* AttackRangeSphere;

	bool IsInAttackRange(float distance) {

		return distance < AttackRangeSphere->GetScaledSphereRadius(); // Return the  Radius of our sphere and if the distance is less then the attack raginf sphere radius its true, if not false

	}


	bool IsInSightRange(float distance) {

		return distance < EnemySightSphere->GetScaledSphereRadius(); // if the player is in the sight range
	}


	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override; // copied from the PlayerChar, same override 


};
