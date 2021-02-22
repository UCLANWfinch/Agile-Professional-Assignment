// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AGILEASSIGNMENT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Shoot();

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ABullet> BulletClass;
	UPROPERTY()
		ABullet* Bullet;
	UPROPERTY(EditAnywhere)
		USceneComponent* projectileSpawnPoint;

	UFUNCTION()
		void Spawn();
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToSpawn;
};
