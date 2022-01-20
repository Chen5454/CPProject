// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"

UCLASS()
class CPPROJECT_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadOnly);  // We want to read it inside the BP we dont want to edit in BP
	bool isWalking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float hp;

	UPROPERTY(BlueprintReadOnly);
	int score;

	UPROPERTY(BlueprintReadOnly);
	bool hasKey;

	UPROPERTY(BlueprintReadWrite);
	bool attackStarted;

	UPROPERTY(BlueprintReadWrite);
	bool dead;

	UPROPERTY(EditAnywhere); //Can see inside Bp AND Editor - 
	UCapsuleComponent* triggerCapsula;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite);
	//bool CanTakeDamage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite);
	//float SafeFallVelocity;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite);
	//float FallDamageMultiplier;

	//FVector PreviousVelocity;


	void MoveForward(float amount);
	void MoveRight(float amount);
	void RotateX(float amount);
	void RotateY(float amount);

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float AttackCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float LastTimeAttack;

	bool canAttack;

	UPROPERTY(EditAnywhere);
	UClass* BPFireball;

	UPROPERTY(EditAnywhere);
	float projectileImpulse;
};
