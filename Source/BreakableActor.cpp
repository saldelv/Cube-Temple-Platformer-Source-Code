// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
	// No tick until it breaks
	SetActorTickEnabled(false);

	// Creating component overlap
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);
}

void ABreakableActor::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If a projectile hits it, play sound and enable tick to destroy it
	if (OtherActor->IsA(AMyProjectile::StaticClass())) {
		UGameplayStatics::PlaySound2D(GetWorld(), BreakSound, 0.15);
		SetActorTickEnabled(true);
	}
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// How long it lives for
	if (Livetime >= 0.f) {
		Livetime -= DeltaTime;
	}
	else {
		//Break object
		Destroy();
	}
}

