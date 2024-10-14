// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}

// Called when the game starts or when spawned
void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// AI 움직임 관련 로직
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 언리얼 서비스 기능으로 대체
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//// AI 시점 기준 현재 플레이어 보이는지 파악
	//if (LineOfSightTo(PlayerPawn))
	//{
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	//}
	//else
	//{
	//	// 플레이어 위치 지우기
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}
}