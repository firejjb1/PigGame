// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FIRSTGAME_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		class UBoxComponent* OverlapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="actor properties")
	float ActorLifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "actor properties")
	int32 ActorLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="components")
	class UStaticMeshComponent* FirstActorMesh;

	class AMainCharacter* ActorToFollow;

	float OffsetToActor = 100.f;

	bool ReachedHome = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

};
