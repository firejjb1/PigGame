// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
AHomeTrigger::AHomeTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AHomeTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHomeTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

