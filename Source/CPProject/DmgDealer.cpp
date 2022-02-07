// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgDealer.h"

#include "Components/BoxComponent.h"
#include "PlayerChar.h"
// Sets default values
ADmgDealer::ADmgDealer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isTrigger = false;

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box")); //Create Damage box == GetComponnent(Unity)

	RootComponent = DamageBox; //Just setting the RootComp to be the DmgBox

	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ADmgDealer::OnBeginOverlap); // this is gonna bind the function on begningoverlap to the OnComponentBeginOverlap - so when we collid with smthing we will know in the function

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(DamageBox); // going to put it below in the hirjaja

}

// Called when the game starts or when spawned
void ADmgDealer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADmgDealer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//void ADmgDealer::TimerFunction() // timer countdown till it will reset
//{
//	CallTracker--;
//
//	if (CallTracker==0)
//	{
//		GetWorldTimerManager().ClearTimer(TimerHandle);
//	}
//	
//}


void ADmgDealer::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp != OtherActor->GetRootComponent())  //when we collide with the root comp, the root comp is what we goona use to coolide/detect with the projectil
	{
		return;
	}

	
		OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this); // passing Damage as param
	

		
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &ADmgDealer::TimerFunction, 3.0f, true, 1.0f);
	
}

