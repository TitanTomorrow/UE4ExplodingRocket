// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyRocketActor.h"
#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> DudeMesh;
		FConstructorStatics()
			: DudeMesh(TEXT("StaticMesh'/Game/Assets/pawn.pawn'")) {}

	};
	static FConstructorStatics ConstructorStatics;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dude"));
	MeshComponent->SetStaticMesh(ConstructorStatics.DudeMesh.Object);
	MeshComponent->AttachTo(RootComponent);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//MeshComponent->SetSimulatePhysics(true);
	//MeshComponent->SetMobility(EComponentMobility::Movable);
	//MeshComponent->SetEnableGravity(false);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	MovementComponent->SetUpdatedComponent(MeshComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(MeshComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector(0.f, 200.f, 100.f);
	CameraBoom->AddLocalRotation(FRotator(-30, 0, 0));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FRotator rot;
	rot = FRotator(0, 0, 0);
	FQuat quat(rot);
	FollowCamera->AddLocalRotation(quat);

	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("TurnRight", this, &AMyPawn::TurnRight);
	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::Fire);
}

void AMyPawn::Fire()
{
	AMyRocketActor::SpawnActor(this);
}

void AMyPawn::MoveForward(float value)
{
	if (value != 0)
	{
		FVector forward = GetActorForwardVector();
		// Apply the input to the character motion
		AddMovementInput(forward, value);
	}

}

void AMyPawn::TurnRight(float value)
{
	if (value != 0)
	{
		AddControllerYawInput(value * 45.0f * GetWorld()->GetDeltaSeconds());
	}
}