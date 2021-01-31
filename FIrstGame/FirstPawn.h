// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FirstPawn.generated.h"

UCLASS()
class FIRSTGAME_API AFirstPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	AFirstPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void E_KeyPressed();
	void E_KeyReleased();
	// 1 when shift is down, otherwise 0
	void ShiftKey(float Value);

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D Direction;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
