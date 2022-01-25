// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"

#include "Components/BoxComponent.h"
#include "Engine/StaticMeshSocket.h"
// Sets default values
ATreasure::ATreasure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;


	TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Treasure"));
	TreasureMesh->SetupAttachment(BoxCollider);

	TreasureFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreasureFrame"));
	TreasureFrameMesh->SetupAttachment(TreasureMesh);

}

// Called when the game starts or when spawned
void ATreasure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

