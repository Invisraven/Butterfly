#include "ALivingEntity.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "ALivingEntity.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//#include "TextureBuildSettings.h"


// Sets default values
AALivingEntity::AALivingEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AALivingEntity::BeginPlay()
{
    Super::BeginPlay();


    GameMode = UGameplayStatics::GetGameMode(GetWorld());
    if (GameMode)
    {
        // Pøístup k promìnné pøes reflection systém Unreal Engine
        Property = GameMode->GetClass()->FindPropertyByName(FName("CurrentYear"));
        if (Property)
        {
            YearOfBorn = *Property->ContainerPtrToValuePtr<int32>(GameMode);
            LastReproduction = 0;
        }
    }


}


// Called every frame
void AALivingEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Property)
      {
        // Pøedpokládejme, že Years je typu int32
        YearsValue = Property->ContainerPtrToValuePtr<int32>(GameMode);
        Age = *YearsValue - YearOfBorn;
        if (YearsValue)
        {
           
           if (LastReproduction < Age)
           {
                TryReproduce();
                Grow();
               LastReproduction = Age;
           }
        }
      }
   

}

void AALivingEntity::TryReproduce()
{
    // Generate a random float between 0 and 1
    float RandomValue = FMath::FRand();
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Trying Reproduce"));
    // If the random value is less than the reproduction chance, spawn a new entity
    if (RandomValue <= ReproductionChance)
    {
        Reproduce();
    }
}

void AALivingEntity::Grow()
{
    if (!FirstEvolution || !SecondEvolution || !ThirdEvolution || !FourEvolution)
    {
        UE_LOG(LogTemp, Error, TEXT("One or more meshes are nullptr!"));
        return;
    }

    if (Age <= VisibilityOfFirstEvolution)
    {   
        FirstEvolution->SetVisibility(true);   
        SecondEvolution->SetVisibility(false);
        ThirdEvolution->SetVisibility(false);
        FourEvolution->SetVisibility(false);
    }
    else if (VisibilityOfFirstEvolution <= Age && Age <= VisibilityOfSecondEvolution)
    {
        FirstEvolution->SetVisibility(false);
        SecondEvolution->SetVisibility(true);
        ThirdEvolution->SetVisibility(false);
        FourEvolution->SetVisibility(false);
    }
    else if (VisibilityOfSecondEvolution <= Age && Age <= VisibilityOfThirdEvolution)
    {
        FirstEvolution->SetVisibility(false);
        SecondEvolution->SetVisibility(false);
        ThirdEvolution->SetVisibility(true);
        FourEvolution->SetVisibility(false);
    }
    else if (VisibilityOfThirdEvolution <= Age && Age <= VisibilityOfFourEvolution)
    {
        FirstEvolution->SetVisibility(false);
        SecondEvolution->SetVisibility(false);
        ThirdEvolution->SetVisibility(false);
        FourEvolution->SetVisibility(true);
    }
    else if (VisibilityOfFourEvolution >= Age)
    {
        FirstEvolution->SetVisibility(false);
        SecondEvolution->SetVisibility(false);
        ThirdEvolution->SetVisibility(false);
        FourEvolution->SetVisibility(false);
    }
    


}

void AALivingEntity::Reproduce()
{


   if (ChildClass)
   {
       
      
        // Získej náhodnou pozici kolem rodièe
        FVector SpawnLocation = OldLocation + FMath::VRand() * ReproductionRadius;
        
        FHitResult HitResult;
        FVector StartLocation = SpawnLocation + FVector(0, 0, 500); // Výchozí bod pro line trace vysoko ve vzduchu
        FVector EndLocation = SpawnLocation - FVector(0, 0, 1000);  // Smìrem dolù pod postavu

        // Line trace
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

        if (bHit)
        {
           SpawnLocation = HitResult.Location;  // Umísti nový objekt na pozici, kde line trace zasáhl
        }
        else
        {
            return;// Pokud line trace nezaznamenal zásah, mùžeš zkusit jiné øešení, napøíklad neprovést spawnování.
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AActor* NewEntity = GetWorld()->SpawnActor<AActor>(ChildClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

    }
}


