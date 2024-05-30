// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoss.h"

// Sets default values
AMyBoss::AMyBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates actor components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);

	HitSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSound"));
	HitSound->SetupAttachment(StaticMesh);

	BossHudClass = nullptr;
	BossHud = nullptr;
}

// Called when the game starts or when spawned
void AMyBoss::BeginPlay()
{
	Super::BeginPlay();
	
	// Sets up overlap event
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);

	// Creates boss health bar hud
	if (BossHudClass) {
		BossHud = CreateWidget<UMyBossHUD>(GetWorld(), BossHudClass, FName(TEXT("BossHudWidget")));
		check(BossHud);
		BossHud->AddToViewport();
	}
}

void AMyBoss::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Update boss health and launch player if hit by a player projectile
	if (OtherActor->IsA(AMyProjectile::StaticClass())) {
		BossHud->UpdateHealth();
		// Reset game instance variables and go back to main menu if the boss is defeated
		if (BossHud->GetHealth() == 0) {
			UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GI->SetCoinCount(0);
			GI->SetHasBow();
			GI->SetHasGrapple();

			UGameplayStatics::OpenLevel(this, LevelToLoad);
		}
		else {
			//Temporarily disable control, teleport to front of boss, and launch character back to start of level after hitting boss
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			Controller->SetInputMode(FInputModeUIOnly());
			Character->GetCharacterMovement()->StopMovementImmediately();
			Character->TeleportTo(GetActorLocation() + FVector(-750, 0, 0), ((GetActorForwardVector())).Rotation());
			Character->LaunchCharacter((FVector(-1, 0, 1) * HitDistance), false, false);
			HitTime = HitTimeDefault;
			Hit = true;
		}
	}
}

// Called every frame
void AMyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Time between attacks
	AttackTime += DeltaTime * Direction;

	// Spawns boss projectile attack at min or max offset time
	if (AttackTime <= 0 || AttackTime >= AttackTimeOffset) {
		FVector SpawnLocation = GetActorLocation() + FVector (-750, -750, 0) + FVector(0, 0, AttackHeight);
		FVector SpawnRotationVector = GetActorForwardVector();
		FRotator SpawnRotation = SpawnRotationVector.Rotation();
		auto SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation, &SpawnRotation) != nullptr;
		
		// Random chance the spawn attack on top and bottom
		float f = FMath::FRand();
		if (f <= 0.3) {
			if (AttackHeight == 0) {
				SpawnLocation = GetActorLocation() + FVector(-750, -750, 0) + FVector(0, 0, AttackHeightOffset);
			}
			else {
				SpawnLocation = GetActorLocation() + FVector(-750, -750, 0);
			}
			auto SpawnedActor2 = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation, &SpawnRotation) != nullptr;
		}

		// Change attack time direction
		Direction *= -1;

		// Alternating attack height
		if (AttackHeight == 0) {
			AttackHeight += AttackHeightOffset;
		}
		else {
			AttackHeight -= AttackHeightOffset;
		}
	}

	// Time while player has no control after being launched
	if (HitTime > 0 && Hit == true) {
		HitTime -= DeltaTime;
	}
	// Giving control back after
	else if (Hit == true) {
		auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		Controller->SetInputMode(FInputModeGameOnly());

		Hit = false;
	}
}

