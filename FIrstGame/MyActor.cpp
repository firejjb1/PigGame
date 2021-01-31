// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "MainCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(FirstActorMesh);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::BeginOverlap);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AMyActor::EndOverlap);

	UE_LOG(LogTemp, Warning, TEXT("name: %s"), *GetName());

	TSubclassOf<AActor> WorldClassObject = AMainCharacter::StaticClass();
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);
	if (ActorsOfClass.Num() > 0) {
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), ActorsOfClass[0]);
		if (NavPath->PathPoints.Num() > 0) {
			for (auto pt : NavPath->PathPoints) {
			//	DrawDebugSphere(GetWorld(), pt, 20.f, 12, FColor::Red, true);
			}
		} 
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
	
	ActorLifetime += DeltaTime;
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	if (ReachedHome) {
		Location.Z = 150.f;
		Rotation.Pitch = 90.f;
		SetActorLocation(Location);
		SetActorRotation(Rotation);
		return;
	}
	// Rotation.Yaw = 45.f * ActorLifetime;
	//UE_LOG(LogTemp, Warning, TEXT("%s Location: (%f, %f, %f), Rotation: (%f, %f, %f)"), *GetName(), Location.X, Location.Y, Location.Z, Rotation.Pitch, Rotation.Yaw, Rotation.Roll); 
	if (!ActorToFollow) {
		// Location.Z += 2.f * DeltaTime;
	}
	else {
		Location = ActorToFollow->GetActorLocation();
		Rotation = ActorToFollow->GetActorRotation();
		float radius = 150.f + 50 * cos(ActorLifetime);
		float angle = 360.f / ActorToFollow->SoulFollowing * (OffsetToActor - 1);
		Location.Z += 10.f * cos(ActorLifetime);
		Location.X += cos(angle * PI / 180.f) * radius;
		Location.Y += sin(angle * PI / 180.f) * radius;
		//Location.Z += 50.f * OffsetToActor;
		// Location.Y += OffsetToActor * 100.f;
		// Rotation.Pitch = 90.f;
	
		// UE_LOG(LogTemp, Warning, TEXT("angle: %f"), angle);

	}
	SetActorLocation(Location);
	SetActorRotation(Rotation);

}

void AMyActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("BeginOVerlap, %s"), *OtherActor->GetName());
	if (!OtherActor || ReachedHome) return;

	if (!ActorToFollow && OtherActor->GetName().Contains("MainCharacter")) {
		// SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
		ActorToFollow = Cast<AMainCharacter>(OtherActor);
		ActorToFollow->SoulFollowing += 1;
		OffsetToActor = ActorToFollow->SoulFollowing;
	}
	if (OtherActor->GetName().Contains("HomeTrigger")) {
		ActorToFollow->SoulFollowing -= 1;
		ActorToFollow = nullptr;
		ReachedHome = true;
	}
	
}

void AMyActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}

