// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableActor.h"

// Sets default values
ACollectableActor::ACollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Execute jump using the physics system and destroys object
void ACollectableActor::Jump(float velocity) {
	if (!IsLaunched) {
		//StaticMesh->AddImpulse({ .0f, .0f, velocity * 500.f });

		UGameplayStatics::PlaySound2D(GetWorld(), CollectSound, 0.3);
		IsLaunched = true;
	}
}

// Called when the game starts or when spawned
void ACollectableActor::BeginPlay()
{
	Super::BeginPlay();

	// Setup per instance OnComponentOverlap event
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);

}

void ACollectableActor::OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Starts collection process if certain class hits it
	if (!IsLaunched && OtherActor->IsA(TriggerClass)) {
		OnJumpTrigger.Broadcast(OtherActor, Component);
	}
}


// Called every frame
void ACollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLaunched) {
		// Decrement livetime
		Livetime -= DeltaTime;

		// Destroy objcet after
		if (Livetime <= 0.f) {
			Destroy();
		}
	}

	// Smoothly rotates actor 
	SetActorRelativeRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));

}

