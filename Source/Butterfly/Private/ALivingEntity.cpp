#include "ALivingEntity.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "ALivingEntity.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AALivingEntity::AALivingEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    ReproductionChance = 0.01f;  // 1% chance per tick
    ReproductionRadius = 500.0f; // Radius for spawning children

}

// Called when the game starts or when spawned
void AALivingEntity::BeginPlay()
{
    Super::BeginPlay();
   
    GameMode = UGameplayStatics::GetGameMode(GetWorld());
    if (GameMode)
    {
        // Zde p�edpokl�d�me, �e prom�nn� "Years" existuje v Blueprint GameMode
        // P��stup k prom�nn� p�es reflection syst�m Unreal Engine
        Property = GameMode->GetClass()->FindPropertyByName(FName("CurrentYear"));
        if (Property)
        {
            // P�edpokl�dejme, �e Years je typu int32
            int32* YearsValue = Property->ContainerPtrToValuePtr<int32>(GameMode);
            LastReproduction = *YearsValue;
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("GameMode nebyl nalezen nebo nen� typu AGameModeBase!"));
    }

}


// Called every frame
void AALivingEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (Property)
      {
        // P�edpokl�dejme, �e Years je typu int32
        int32* YearsValue = Property->ContainerPtrToValuePtr<int32>(GameMode);
        if (YearsValue)
        {
           
           if (LastReproduction < *YearsValue)
           {
                TryReproduce();
                LastReproduction = *YearsValue;
           }
        }
      }
    else
    {
      GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Prom�nn� 'Years' nebyla nalezena v GameMode!"));
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

void AALivingEntity::Reproduce()
{


   if (ChildClass)
   {
       
      
        // Z�skej n�hodnou pozici kolem rodi�e
        FVector SpawnLocation = OldLocation + FMath::VRand() * ReproductionRadius;
        
        FHitResult HitResult;
        FVector StartLocation = SpawnLocation + FVector(0, 0, 500); // V�choz� bod pro line trace vysoko ve vzduchu
        FVector EndLocation = SpawnLocation - FVector(0, 0, 1000);  // Sm�rem dol� pod postavu

        // Line trace
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

        if (bHit)
        {
           SpawnLocation = HitResult.Location;  // Um�sti nov� objekt na pozici, kde line trace zas�hl
        }
        else
        {
            return;// Pokud line trace nezaznamenal z�sah, m��e� zkusit jin� �e�en�, nap��klad neprov�st spawnov�n�.
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AActor* NewEntity = GetWorld()->SpawnActor<AActor>(ChildClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        // P�idej debug zpr�vu
       /* if (NewEntity && GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("New entity spawned!"));
        }
        */
    }
}


