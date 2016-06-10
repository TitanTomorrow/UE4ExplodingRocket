// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyRocketActor.generated.h"

UCLASS()
class MYPROJECT_API AMyRocketActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Rocket, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* MovementComponent;

	void Explode(bool destroy);
	FVector _shootDirection;
	bool bExploded;

	void Shoot(FRotator& ShootDirection);
protected:
	virtual void Destroyed() override;
	
public:	
	// Sets default values for this actor's properties
	AMyRocketActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	static AMyRocketActor* SpawnActor(AActor *owner);
	
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
