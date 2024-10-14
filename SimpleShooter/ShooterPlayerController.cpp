// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"

// build.cs ���Ͽ��� PublicDependencyModuleNames���� UMG �߰��ؾ� ��� ����
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDClass);

	if (HUDScreen != nullptr)
	{
		// ũ�ν���� ǥ��
		HUDScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// ���� ����� ũ�ν���� ����
	HUDScreen->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

		if (WinScreen != nullptr)
		{
			// �¸� ���� ȭ�鿡 ǥ��
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

		if (LoseScreen != nullptr)
		{
			// �й� ���� ȭ�鿡 ǥ��
			LoseScreen->AddToViewport();
		}
	}

	// ���� �����
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
