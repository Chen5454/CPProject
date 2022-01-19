// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "Components/CapsuleComponent.h"

#include "Projectile.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
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


	triggerCapsula = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	triggerCapsula->InitCapsuleSize(55.0f, 96.0f); // Size of the Capsule
	triggerCapsula->GetComponentRotation();
	triggerCapsula->SetCollisionProfileName(TEXT("Trigger")); // name for our Capsule
	triggerCapsula->SetupAttachment(RootComponent);

	triggerCapsula->OnComponentBeginOverlap.AddDynamic(this, &APlayerChar::OnOverlapBegin);

	projectileImpulse = 5000;
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
	if (LastTimeAttack> AttackCD&& !canAttack)
	{
		canAttack = true;
		LastTimeAttack = 0;
	}

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

void APlayerChar::RotateX(float amount)
{
	AddControllerYawInput(100.0f * amount * GetWorld()->GetDeltaSeconds());  // Time.DeltaTime Unity Thingy for frame
}

void APlayerChar::RotateY(float amount)
{
	AddControllerPitchInput(100.0f * amount * GetWorld()->GetDeltaSeconds());
}

void APlayerChar::OnAttack()
{
	attackStarted = true;

	if (canAttack)
	{
		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("CATRigRibcage003Bone001"); // Need to added the Bone

		nozzle += fwd * 55;

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(BPFireball,nozzle,RootComponent->GetComponentRotation());

		canAttack = false;
		if (projectile)
		{
			projectile->ColisionSphere->AddImpulse(fwd * projectileImpulse);
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

		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);  //Restart Level/Game
	}

	return 0.0f;
}

void APlayerChar::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{




}


