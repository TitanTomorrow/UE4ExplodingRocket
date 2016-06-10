// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyExplosionActor.generated.h"

UCLASS()
class MYPROJECT_API AMyExplosionActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent *MeshComponent;

	float _time;

public:	
	// Sets default values for this actor's properties
	AMyExplosionActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	static void Explode(class AActor *owner, const FVector& location);
	
};
