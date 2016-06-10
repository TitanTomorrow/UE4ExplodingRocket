// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyTargetActor.h"


// Sets default values
AMyTargetActor::AMyTargetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> DudeMesh;
		FConstructorStatics()
			: DudeMesh(TEXT("StaticMesh'/Game/Assets/pawn.pawn'")) {}
	};
	static FConstructorStatics ConstructorStatics;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetStaticMesh(ConstructorStatics.DudeMesh.Object);
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
}

// Called when the game starts or when spawned
void AMyTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTargetActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator rot = this->GetActorRotation();
	rot.Yaw += FMath::Lerp(0.0f, 45.0f, DeltaTime);
	this->SetActorRotation(rot);
}

float AMyTargetActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	this->Destroy();
	return DamageAmount;
}

