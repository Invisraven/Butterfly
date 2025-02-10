// Fill out your copyright notice in the Description page of Project Settings.


#include "AGrass.h"
//#include "TextureBuildSettings.h"

AAGrass::AAGrass()
{
    PrimaryActorTick.bCanEverTick = true;

    // Uisti sa, že ALivingEntity má tieto komponenty správne inicializované
    FirstEvolution = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstEvolution"));
    SecondEvolution = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondEvolution"));
    ThirdEvolution = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdEvolution"));
    FourEvolution = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FourEvolution"));

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    FirstEvolution->SetupAttachment(RootComponent);
    SecondEvolution->SetupAttachment(RootComponent);
    ThirdEvolution->SetupAttachment(RootComponent);
    FourEvolution->SetupAttachment(RootComponent);
    VisibilityOfFirstEvolution = 10;
    VisibilityOfSecondEvolution = 20;
    VisibilityOfThirdEvolution = 40;
    VisibilityOfFourEvolution = 80;
    ReproductionChance = 0.01f;  // 1% chance per tick
    ReproductionRadius = 500.0f; // Radius for spawning children

    // Naèítanie meshov iba raz pri spustení hry
    static ConstructorHelpers::FObjectFinder<UStaticMesh> FirstMeshAsset(TEXT("/Game/MWLandscapeAutoMaterial/Meshes/Plants/SM_MWAM_GrassD"));
    if (FirstMeshAsset.Succeeded())
    {
        FirstEvolution->SetStaticMesh(FirstMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SecondMeshAsset(TEXT("/Game/MWLandscapeAutoMaterial/Meshes/Plants/SM_MWAM_GrassC"));
    if (SecondMeshAsset.Succeeded())
    {
        SecondEvolution->SetStaticMesh(SecondMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ThirdMeshAsset(TEXT("/Game/MWLandscapeAutoMaterial/Meshes/Plants/SM_MWAM_GrassB"));
    if (ThirdMeshAsset.Succeeded())
    {
        ThirdEvolution->SetStaticMesh(ThirdMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> FourMeshAsset(TEXT("/Game/MWLandscapeAutoMaterial/Meshes/Plants/SM_MWAM_GrassA"));
    if (FourMeshAsset.Succeeded())
    {
        FourEvolution->SetStaticMesh(FourMeshAsset.Object);
    }

    FirstEvolution->SetVisibility(false);
    SecondEvolution->SetVisibility(false);
    ThirdEvolution->SetVisibility(false);
    FourEvolution->SetVisibility(false);

    
}

