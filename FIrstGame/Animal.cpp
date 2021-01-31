// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "AnimalController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "HomeTrigger.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FVector Location = GetActorLocation();
	PatrolPoint1 = Location;
	PatrolPoint2 = Location;
	PatrolPoint3 = Location;
	PatrolPoint4 = Location;
	PatrolPoint1.X += 1000.f;
	PatrolPoint2.Y += 1000.f;
	PatrolPoint3.X -= 1000.f;
	PatrolPoint4.Y -= 1000.f;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	// RootComponent = AgroSphere;
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AAnimal::BeginOverlap);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AAnimal::EndOverlap);
	AgroSphere->SetSphereRadius(200.f);
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = GetActorLocation();
	AnimalController = Cast<AAnimalController>(GetController());
	

	AnimalController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint1"), PatrolPoint1 + Location);
	AnimalController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint2"), PatrolPoint2 + Location);
	AnimalController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint3"), PatrolPoint3 + Location);
	FVector EndGoal(-480.f, -100.f, 130.f);
	AnimalController->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint4"), EndGoal);

}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetActor) {
		FVector TargetLoc = TargetActor->GetActorLocation();
		FVector Location = GetActorLocation();

		FVector Direction(Location.X - TargetLoc.X, Location.Y - TargetLoc.Y, 0.f);
		AddMovementInput(Direction, 10.f);
		FRotator Rotation = GetActorRotation();
		Rotation.Pitch = 90.f;
		SetActorRotation(Rotation);
	}
}

// Called to bind functionality to input
void AAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("BeginOVerlap, %s"), *OtherActor->GetName());
	if (OtherActor && !ReachedHome) {
		if (OtherActor->GetName().Contains("HomeTrigger")) {
			TargetActor = nullptr;
			ReachedHome = true;
			return;
		}
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);

		if (Main) {
			TargetActor = Main;
			if (AnimalController == nullptr)
				AnimalController = Cast<AAnimalController>(GetController());
			AnimalController->GetBlackboard()->SetValueAsObject(TEXT("TargetActor"), Main);
		}

		

		if (TargetActor) {
			TSubclassOf<AActor> WorldClassObject = AHomeTrigger::StaticClass();
			TArray<AActor*> ActorsOfClass;
			UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);
			if (ActorsOfClass.Num() > 0) {
				UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), ActorsOfClass[0]);
				if (NavPath->PathPoints.Num() > 0) {
					AddMovementInput(NavPath->PathPoints[0], 1.f);
					for (auto pt : NavPath->PathPoints) {
						DrawDebugSphere(GetWorld(), pt, 20.f, 12, FColor::Red, true);
						
					}
				}
			}
		}

		
	}

}

void AAnimal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}

