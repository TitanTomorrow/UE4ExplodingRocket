// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MyProjectGameMode.h"

#include "MyPawn.h"


AMyProjectGameMode::AMyProjectGameMode()
{
	//ConstructorHelpers::FClassFinder<ABluePrintPawn> pawn = ConstructorHelpers::FClassFinder<ABluePrintPawn>(TEXT("/Game/assets/ABluePrintPawn"));
	//if (pawn.Class != NULL)
	{
		DefaultPawnClass = AMyPawn::StaticClass();
	}

}