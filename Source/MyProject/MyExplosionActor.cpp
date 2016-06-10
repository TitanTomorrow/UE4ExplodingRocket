// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyExplosionActor.h"


// Sets default values
AMyExplosionActor::AMyExplosionActor() :
	_time(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> DudeMesh;
		FConstructorStatics()
			: DudeMesh(TEXT("StaticMesh'/Game/Assets/explosion.explosion'")) {}

	};
	static FConstructorStatics ConstructorStatics;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Star"));
	MeshComponent->SetStaticMesh(ConstructorStatics.DudeMesh.Object);
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

// Called when the game starts or when spawned
void AMyExplosionActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(1.0f);
	
}

// Called every frame
void AMyExplosionActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	_time += DeltaTime;
	float scale = FMath::Lerp(4.0f, 20.0f, _time);
	this->SetActorScale3D(FVector(scale, scale, scale));
}


void AMyExplosionActor::Explode(class AActor *owner, const FVector& location)
{
	FTransform SpawnTM(FRotator::ZeroRotator, location);
	AMyExplosionActor *sphere = Cast<AMyExplosionActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(owner, AMyExplosionActor::StaticClass(), SpawnTM));
	if (sphere)
	{
		sphere->SetOwner(owner);
		sphere->_time = 0;
		UGameplayStatics::FinishSpawningActor(sphere, SpawnTM);
	}
}