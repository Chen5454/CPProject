// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerChar.h"
#include "Projectile.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20;
	Hp = 100;
	EnemyAttackCD = 1.5;
	LastTimeEnemyAttack = 0;

	ProjectilImpulse = 2000;
	EnemySightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	EnemySightSphere->SetupAttachment(RootComponent);


	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Attack(AActor* AttackTarget)
{
}

float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

