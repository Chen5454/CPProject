// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isActivatable){

		FVector ActorLocation = GetActorLocation();
		ActorLocation.Y += platformSpeed;

		if (isDiagonal)
			ActorLocation.Z += platformSpeed;

			SetActorLocation(ActorLocation);

			if (ActorLocation.Y >=firstEnd)
			{
				platformSpeed *= -1.0f;
			}

			if (ActorLocation.Y <= secondEnd)
			{
				platformSpeed *= -1.0f;
			}

	}else if (isActivatable && activated)
	{
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Y += platformSpeed;

		SetActorLocation(ActorLocation);

		if (ActorLocation.Y >= firstEnd)
		{
			platformSpeed *= -1.0f;
		}

		if (ActorLocation.Y <= secondEnd)
		{
			platformSpeed *= -1.0f;
		}



	}

}

void AMovingPlatform::TogglePlatform()
{

	isActivatable = false;



}

