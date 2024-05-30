// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates projectile components
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

	// Sets projectile default settings
	ProjectileComponent->InitialSpeed = 1000;
	ProjectileComponent->MaxSpeed = 2000;
	ProjectileComponent->ProjectileGravityScale = 0;
	ProjectileComponent->Velocity *= -1;
}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Sets up overlap event
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);
}

void AMyProjectile::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//if (!(OtherActor->IsA(AMyProjectile::StaticClass()))) {
		//ConditionalBeginDestroy();
	//}
}

// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Time before projectile is destoryed automatically
	if (LiveTime >= 0) {
		LiveTime -= DeltaTime;
	}
	else {
		// Destorys projectile
		Destroy();
	}

}

