// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/World.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = -20.0f;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, -5.0f, 0.0f));

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(RootComponent);
	projectileSpawnPoint->SetRelativeLocation(FVector(100.0f, 0.0f, 50.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Spawn"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Spawn);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
}


void APlayerCharacter::LookUp(float AxisValue)
{
	if (AxisValue)
	{
		float tempRot = SpringArm->GetRelativeRotation().Pitch + AxisValue;
		if (tempRot < 15 && tempRot > -50)
		{
			SpringArm->AddLocalRotation(FRotator(AxisValue, 0.0f, 0.0f));
		}
	}
}

void APlayerCharacter::LookRight(float AxisValue)
{
	if (AxisValue)
	{
		AddControllerYawInput(AxisValue);
	}
}

void APlayerCharacter::Shoot()
{
	if (BulletClass) //checks if bullet is set as projectile
	{
		FVector location = projectileSpawnPoint->GetComponentLocation();
		FRotator rotation = projectileSpawnPoint->GetComponentRotation();

		ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, location, rotation);
		TempBullet->SetOwner(this);
	}
}

void APlayerCharacter::Spawn()
{
	UWorld* World = GetWorld();
	FVector Location = FVector(-2340.0f, -2310.0f, 60.0f);
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

	World->SpawnActor(ActorToSpawn, &Location, &Rotation);
	UE_LOG(LogTemp, Warning, TEXT("Spawned"));
}