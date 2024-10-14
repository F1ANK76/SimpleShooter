// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	// �÷��̾� ����
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	// ���忡 �ִ� ��� ��Ʈ�ѷ� ����
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		// AI�� ����ִٸ� �� �������� ���� �������� ����
		if (!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// ���忡 �ִ� ��� ��Ʈ�ѷ� ����
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// �÷��̾� �Ǵ� AI�� �̱�� ���� �Ǵ�
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
