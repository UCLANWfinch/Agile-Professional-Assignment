// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "EnemyAIController.h"
#include "Waypoint.h"

#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);

	MoveToWaypoints();

	currentHealth = MaxHealth;
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead())
	{
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void AEnemyAI::MoveToWaypoints()
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());
	
	if (EnemyAIController)
	{
		if (CurrentWaypoint <= Waypoints.Num()) {
			for (AActor* Waypoint: Waypoints)
			{
				AWaypoint* WaypointItr = Cast<AWaypoint>(Waypoint);

				if (WaypointItr->GetWaypointOrder() == CurrentWaypoint)
				{
					EnemyAIController->MoveToActor(WaypointItr, 20.0f, false);
					CurrentWaypoint++;
					break;
				}
			}
		}
		else
		{
			Destroy();
		}
	}
}

bool AEnemyAI::IsDead() const
{
	return currentHealth <= 0;
}



