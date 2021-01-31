// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalController.h"
#include "Animal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AAnimalController::AAnimalController() {
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);  
}

void AAnimalController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	if (InPawn == nullptr) return;
	AAnimal* Animal = Cast<AAnimal>(InPawn);
	if (Animal) {
		if (Animal->BehaviorTree) {
			BlackboardComponent->InitializeBlackboard(*(Animal->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(Animal->BehaviorTree));

		}
	}
}

UBlackboardComponent* AAnimalController::GetBlackboard() {
	return BlackboardComponent;
}
