// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

#include "Components/CapsuleComponent.h"

#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"

#include "Kismet/GameplayStatics.h"

#include "PickUpItem.h"

//#include "PickupItems.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCD = 1.5f;
	canAttack = true;
	attackStarted = false;
	LastTimeAttack = 0.0f;
	Score = 0;
	//***Character Falling Damage Properties****
	
	//PreviousVelocity = FVector(0.f, 0.f, 0.f);
	//CanTakeDamage = false;
	//SafeFallVelocity = 1000.f;
	//FallDamageMultiplier = .1f;

	TriggerCapsula = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsula->InitCapsuleSize(55.0f, 96.0f); // Size of the Capsule
	TriggerCapsula->SetCollisionProfileName(TEXT("Trigger")); // name for our Capsule
	TriggerCapsula->SetupAttachment(RootComponent);

	TriggerCapsula->OnComponentBeginOverlap.AddDynamic(this, &APlayerChar::OnOverlapBegin); //this is gonna bind the function on begningoverlap to the OnComponentBeginOverlap

	//triggerCapsula->OnComponentBeginOverlap.AddDynamic(this, &APlayerChar::OnOverlapBegin);

	projectileImpulse = 5000; //the "speed"/explosion of the projectile
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastTimeAttack += DeltaTime;
	if (LastTimeAttack> AttackCD&& !canAttack) //timer for attack. 
	{
		canAttack = true;
		LastTimeAttack = 0;
	}
	

	//****Character Falling damage calculation - not working******



	//if (!CanTakeDamage) return;

	//// We deal with some big numbers here to avoid using sqrtf() every tick

	//FVector Velocity = GetCharacterMovement()->Velocity.GetAbs();
	//FVector DeltaVelocitySquared = (Velocity - PreviousVelocity.GetAbs()) * (Velocity - PreviousVelocity.GetAbs());
	//float DeltaSpeed = DeltaVelocitySquared.X + DeltaVelocitySquared.Y + DeltaVelocitySquared.Z;

	//if (DeltaSpeed > (SafeFallVelocity * SafeFallVelocity))
	//{
	//	// In this case, we have a sudden stop, and one that's sudden enough to cause damage. This should be rare enough that we can afford a sqrtf()
	//	float Damage = sqrtf(DeltaSpeed) * FallDamageMultiplier;
	//	TakeDamage(Damage, FDamageEvent(), GetController(), this);
	//}

	//PreviousVelocity = Velocity;

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent); //checks that PlayerInputComponent is valid and not null
	PlayerInputComponent->BindAxis("Forward", this, &APlayerChar::MoveForward);  // this is the name of the axis and for the oressing key we will call that axis forward (S or W).
	PlayerInputComponent->BindAxis("Right", this, &APlayerChar::MoveRight);
	PlayerInputComponent->BindAxis("RotateX", this, &APlayerChar::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &APlayerChar::RotateY);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerChar::Jump); // Action - When WE pressed the key
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerChar::OnAttack);

	//PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerChar::OnAttack);  // Later added Attack
}

void APlayerChar::MoveForward(float amount)
{
	if (Controller && amount !=0)
	{
		isWalking = true;

		FVector fwd = GetActorForwardVector();
		AddMovementInput(fwd, amount);
	}

	if (amount == 0)
		isWalking = false;
}

void APlayerChar::MoveRight(float amount)
{
	if (Controller && amount != 0)
	{

		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}

}

// mouse Rotation x and Y for controller

void APlayerChar::RotateX(float amount)
{
	AddControllerYawInput(50.0f * amount * GetWorld()->GetDeltaSeconds());  // Time.DeltaTime Unity Thingy for frame
}

void APlayerChar::RotateY(float amount)
{
	AddControllerPitchInput(50.0f * amount * GetWorld()->GetDeltaSeconds());
}

void APlayerChar::OnAttack()
{

	//When we start attacking -

	attackStarted = true;

	if (canAttack)
	{
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("CATRigRibcage003Bone001"); // Need to added the Bone - nozzle - where we want the projectile to go from

		nozzle += fwd * 55; // we multiply the vector so it wont collide with our mesh/collide

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(BPFireball,nozzle,RootComponent->GetComponentRotation());  //we need to specify the location and the rotation for out projectile that we are gonna spawn
		canAttack = false; // after we attack we disable the attack - for the cd

		if (projectile) // if we spawned an projectile
		{
			projectile->ColisionSphere->AddImpulse(fwd * projectileImpulse); //launch the projectile
		}

	}

}

float APlayerChar::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	hp -= Damage;

	if (hp <= 0)
	{
		hp = 0;


		dead = true;

		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);  //Restart Level/Game
	}



	return 0.0f;
}


void APlayerChar::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (Cast<APickUpItem>(OtherActor)) // cast to the pickup item. if the other actor we collide with is from Class APickupitem if so .. so
	{
		if (OtherActor->ActorHasTag("Key"))
		{

			hasKey = true;
			Score += 500;
			UE_LOG(LogTemp, Warning, TEXT("Key"));

		}

		else if (OtherActor->ActorHasTag(("Gem")))
		{

			Score += 1000;
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("COLLIDE"));

			Score += 100;
		}

		UE_LOG(LogTemp, Warning, TEXT("The Score is:  %d"), Score);

		
		
		OtherActor->Destroy();
	}




}


//void APlayerChar::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("COLLIDE"));
//
//		
//			Score += 100;
//
//		
//		OtherActor->Destroy();
//	
//}


