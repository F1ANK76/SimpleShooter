// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"

// build.cs 파일에서 PublicDependencyModuleNames에서 UMG 추가해야 사용 가능
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDScreen = CreateWidget(this, HUDClass);

	if (HUDScreen != nullptr)
	{
		// 크로스헤어 표시
		HUDScreen->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// 게임 종료시 크로스헤어 제거
	HUDScreen->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

		if (WinScreen != nullptr)
		{
			// 승리 위젯 화면에 표시
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

		if (LoseScreen != nullptr)
		{
			// 패배 위젯 화면에 표시
			LoseScreen->AddToViewport();
		}
	}

	// 게임 재시작
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
