// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	// 플레이어 죽음
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// 월드에 있는 모든 컨트롤러 추출
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		// AI가 살아있다면 얼리 리턴으로 게임 종료하지 않음
		if (!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// 월드에 있는 모든 컨트롤러 추출
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// 플레이어 또는 AI가 이기는 유무 판단
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
