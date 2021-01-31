// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFirstPawn::AFirstPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(Cast<USceneComponent>(MeshComponent));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	Speed = 500.f;
	Direction = FVector2D(0.f, 0.f);
}

// Called when the game starts or when spawned
void AFirstPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFirstPawn::E_KeyPressed() {

}

void AFirstPawn::E_KeyReleased() {

}

void AFirstPawn::ShiftKey(float Value) {

}

void AFirstPawn::MoveForward(float Value) {
	Direction.X = Value;
	if (Value != 0.0f) {

	}
}

void AFirstPawn::MoveRight(float Value) {
	Direction.Y = Value;
	if (Value != 0.0f) {

	}
}

// Called every frame
void AFirstPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	FVector DeltaLocation = FVector(Direction.X, Direction.Y, 0.f);
	DeltaLocation.Normalize();
	DeltaLocation *= Speed * DeltaTime;
	Location += DeltaLocation;
	SetActorLocation(Location);
}

// Called to bind functionality to input
void AFirstPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// action mappings
	PlayerInputComponent->BindAction("E_Key", IE_Pressed, this, &AFirstPawn::E_KeyPressed);
	PlayerInputComponent->BindAction("E_Key", IE_Released, this, &AFirstPawn::E_KeyReleased);

	// axis mappings
	PlayerInputComponent->BindAxis("SHIFT_Key", this, &AFirstPawn::ShiftKey);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPawn::MoveRight);

}

