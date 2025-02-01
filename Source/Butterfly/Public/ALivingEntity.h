// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "ALivingEntity.generated.h"


UCLASS()
class BUTTERFLY_API AALivingEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	AALivingEntity();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to spawn a new entity
	UFUNCTION(BlueprintCallable, Category = "Reproduction")
	void Reproduce();

	// Reproduction logic
	void TryReproduce();

	UFUNCTION(BlueprintCallable, Category = "Grow")
	void Grow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AGameModeBase* GameMode;
	FProperty* Property;
	
	
public:
	// Variables for reproduction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reproduction")
	float ReproductionChance; // % chance to reproduce each tick

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reproduction")
	float ReproductionRadius; // Radius around the parent for spawning

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reproduction")
	FVector OldLocation;

	int32 LastReproduction;
	int32* YearsValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	int32 VisibilityOfFirstEvolution;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	UStaticMeshComponent* FirstEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	int32 VisibilityOfSecondEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	UStaticMeshComponent *SecondEvolution;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	int32 VisibilityOfThirdEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	UStaticMeshComponent *ThirdEvolution;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	int32 VisibilityOfFourEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grow")
	UStaticMeshComponent *FourEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reproduction")
	TSubclassOf<AActor> ChildClass; // Class of the entity to spawn

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UChildActorComponent* ChildActorComponent;


};

