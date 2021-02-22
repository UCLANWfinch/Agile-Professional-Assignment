// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "EnemyAI.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movementSpeed = 3000.0f;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetSimulatePhysics(true);

	projecileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projecileMovementComponent->MaxSpeed = movementSpeed;
	projecileMovementComponent->InitialSpeed = movementSpeed;
	projecileMovementComponent->bRotationFollowsVelocity = true;
	projecileMovementComponent->bShouldBounce = false;
	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();

	if (!ProjectileOwner)
	{
		return;
	}
	if (OtherActor->GetClass()->IsChildOf(AEnemyAI::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
		UGameplayStatics::ApplyDamage(OtherActor, //actor that will be damaged
			100.0f, // base damage applied
			ProjectileOwner->GetInstigatorController(), // controller that was responsible for causing the damage
			this, // actor that actually that caused the damage 
			UDamageType::StaticClass()); //class that describes the damage done
		Destroy();
	}
}

