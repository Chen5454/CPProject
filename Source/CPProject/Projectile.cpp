// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Shpere"));
	
	RootComponent = ColisionSphere;
	ColisionSphere->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnOverlapBegin);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(ColisionSphere);

	Damage = 50;//Testing

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Here we gonna apply the Damage - we will call other actor

	if (OtherComp!= OtherActor->GetRootComponent())  //when we collide with the root comp, the root comp is what we goona use to coolide/detect with the projectil
	{
		return;
	}

	OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);


	Destroy();

}

