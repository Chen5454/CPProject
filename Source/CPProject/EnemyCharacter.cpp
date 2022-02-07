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

	//Speed = 20;
	Hp = 100;
	EnemyAttackCD = 1.5;
	LastTimeEnemyAttack = 0;

	ProjectilImpulse = 2000;
	EnemySightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere")); //GetComponent -Create Sphere for the sight
	EnemySightSphere->SetupAttachment(RootComponent);


	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere")); //GetComponent -Create Sphere for the Range
	AttackRangeSphere->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerChar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); // getting ref for player 

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//calculate player location

	FVector playerPos = PlayerRef->GetActorLocation(); // get the player location
	FVector distance = playerPos - GetActorLocation(); // the diffrents from player location to the monster enemy 
	float distanceToPlayer = distance.Size(); // getting the size of the distance diffrent will be how far the player is away from the enemy

	// rotate the enemy to the player
	FRotator toPlayerRotation = distance.Rotation(); 
	toPlayerRotation.Pitch = 0; // we are not going to rotate him on the pitch

	if (!IsEnemyDead)
	{
		RootComponent->SetWorldRotation(toPlayerRotation);
	}



	if (distanceToPlayer > EnemySightSphere->GetScaledSphereRadius()) // if the distance is higher- which means enemy cant see player
	{
		IsEnemyAttacking = false;
		return;
	}

	if (IsInAttackRange(distanceToPlayer)&&!IsEnemyDead) // if the player is in the attack range and not dead
	{
		if (LastTimeEnemyAttack ==0) // if we cooled down we will attack
		{
			Attack(PlayerRef);
		}

		LastTimeEnemyAttack += DeltaTime;
		if (LastTimeEnemyAttack>EnemyAttackCD)
		{
			LastTimeEnemyAttack = 0; // reset the attack timer
		}

		return;
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Attack(AActor* AttackTarget)
{

	UE_LOG(LogTemp, Warning, TEXT("Enenmy is attacking"));  //Testing that the collider working while collide :D

	if (BPProjectile) // if we do have the Projectile (we need to attatch the bp projectile inside the bp)
	{
		IsEnemyAttacking = true;
		FVector fwd = GetActorForwardVector(); // going to get the forword vector of the enemy
		FVector nozzle = GetMesh()->GetBoneLocation("Mouth_end"); // same as the player, we need the string of the bone for spawning  projectile

		nozzle += fwd * 55;  // we multiply the vector so it wont collide with our mesh/collide


		FVector ToOpponent = AttackTarget->GetActorLocation() - nozzle; // give us the diffrence in the range between the enemy and player

		ToOpponent.Normalize(); 

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(BPProjectile, nozzle, RootComponent->GetComponentRotation()); //we need to specify the location and the rotation for out projectile that we are gonna spawn

		if (projectile) // if the projectile spawned
		{
			projectile->ColisionSphere->AddImpulse(fwd * ProjectilImpulse); //launch the projectile
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No BPProjectile Found"));
	}

}

float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Hp -= Damage;

	if (Hp<=0)
	{
		IsEnemyDead = true;
	}



	return 0.0f;
}

