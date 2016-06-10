// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyRocketActor.h"
#include "MyExplosionActor.h"


// Sets default values
AMyRocketActor::AMyRocketActor() :
	bExploded(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> DudeMesh;
		FConstructorStatics()
			: DudeMesh(TEXT("StaticMesh'/Game/Assets/star.star'")) {}

	};
	static FConstructorStatics ConstructorStatics;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Star"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetStaticMesh(ConstructorStatics.DudeMesh.Object);
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("RocketMovement"));
	MovementComponent->SetUpdatedComponent(MeshComponent);
	MovementComponent->InitialSpeed = 3000;


}

// Called when the game starts or when spawned
void AMyRocketActor::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(0.5f);
}

// Called every frame
void AMyRocketActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

AMyRocketActor* AMyRocketActor::SpawnActor(AActor *owner)
{
	FVector location = owner->GetRootComponent()->GetSocketLocation(TEXT("Socket"));
	FRotator rotation = owner->GetRootComponent()->GetSocketRotation(TEXT("Socket"));
	FTransform SpawnTM(rotation, location);
	SpawnTM.SetScale3D(FVector(0.1, 0.1, 0.1));
	AMyRocketActor *projectile = Cast<AMyRocketActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		owner, AMyRocketActor::StaticClass(), SpawnTM));
	if (projectile)
	{
		projectile->SetOwner(owner);
		UGameplayStatics::FinishSpawningActor(projectile, SpawnTM);
	}
	return projectile;
}

void AMyRocketActor::Destroyed()
{
	if (!bExploded)
	{
		Explode(false);
	}
}

void AMyRocketActor::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	Explode(true);
}

void AMyRocketActor::Explode(bool destroy)
{
	if (bExploded == false)
	{
		// effects and damage origin shouldn't be placed inside mesh at impact point
		const FVector loc = GetActorLocation();

		APawn *pawn = Cast<APawn>(GetOwner());
		AController *controller = NULL;
		if (pawn != NULL)
		{
			controller = pawn->GetController();
		}

		UGameplayStatics::ApplyRadialDamage(this, 100.0f, loc, 100.0f, UDamageType::StaticClass(), TArray<AActor*>(), this, controller, true);
		bExploded = true;
		AMyExplosionActor::Explode(this->GetOwner(), loc);
		if (destroy)
			this->Destroy();
	}
}