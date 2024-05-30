// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates player components
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());

	PlayerCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraBoom"));
	PlayerCameraBoom->SetupAttachment(GetCapsuleComponent());
	PlayerCameraBoom->TargetArmLength = CameraLength;
	PlayerCameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerCameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	BowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowMesh"));
	BowMesh->SetupAttachment(PlayerMesh);

	GrappleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrappleMesh"));
	GrappleMesh->SetupAttachment(PlayerMesh);

	GrappleLine = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleLine"));
	GrappleLine->SetupAttachment(PlayerMesh);

	PlayerHudClass = nullptr;
	PlayerHud = nullptr;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Sets up overlap event
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	PlayerMesh->OnComponentBeginOverlap.Add(DelegateSubscriber);

	// Creates player hud and uses game instance values and disables it if on the main menu
	if (IsLocallyControlled() && PlayerHudClass && GetWorld()->GetName() != "MainMenuMap") {
		PlayerHud = CreateWidget<UMyHUD>(GetWorld(), PlayerHudClass, FName(TEXT("HudWidget")));
		check(PlayerHud);
		PlayerHud->AddToViewport();
		PlayerHud->SetCointCount();
	}

	// Sets correct walk speed and air control
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->AirControl = InAirControl;
	
	// Decides if bow or grapple items should be visible and usable based on game instance
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BowPickedUp = GI->GetHasBow();
	if (BowPickedUp == false) {
		BowMesh->SetVisibility(false);
	}
	GrapplePickedUp = GI->GetHasGrapple();
	if (GrapplePickedUp == false) {
		GrappleMesh->SetVisibility(false);
		GrappleLine->SetVisibility(false);
	}
}

void AMyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	// Removes player hud
	if (PlayerHud) {
		PlayerHud->RemoveFromParent();
		PlayerHud = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void AMyCharacter::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Updates coin count if a coin is collected
	if (OtherActor->IsA(CoinActor)) {
		UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GI->SetCoinCount(GI->GetCoinCount() + 1);

		PlayerHud->SetCointCount();
	}
	// Teleports play if hit by a boss attack
	else if (OtherActor->IsA(ActorClassToBeHitBy)) {
		TeleportTo(BossTeleport, GetActorForwardVector().Rotation());
	}
	// Makes bow visible and usable if bow item is picked up
	else if (OtherActor->IsA(BowActorClass)) {
		BowMesh->SetVisibility(true);
		BowPickedUp = true;

		UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GI->SetHasBow();
	}
	// Makes grapple visible and usable if grapple item is picked up
	else if (OtherActor->IsA(GrappleActorClass)) {
		GrappleMesh->SetVisibility(true);
		GrapplePickedUp = true;

		UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GI->SetHasGrapple();
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement to point before GrappleFinished done in blueprint to get sweep results correctly
	//
	// Keeps character in place when reached grapple hit point but button not released
	if (IsGrappling && GrappleFinished) {
		GetCharacterMovement()->StopMovementImmediately();
	}

	if ((GetCharacterMovement()->IsFalling())) {
	}

	// Resets dash, jump, and grapple usability after touching the ground
	if (!(GetCharacterMovement()->IsFalling())) {
		HasDashed = false;
		HasDashedGround = false;
		DashFinished = false;
		DashTime = DashTimeDefault;
		CanJump = true;
		Grappled = false;
	}

	// Resets sprint if movement stops
	if(GetCharacterMovement()->Velocity.X == FVector::ZeroVector.X && GetCharacterMovement()->Velocity.Y == FVector::ZeroVector.Y) {
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	//FRotator CharacterRotation = GetCapsuleComponent()->GetComponentRotation();
	//CharacterRotation.Yaw = GetControlRotation().Yaw;
	//GetCapsuleComponent()->SetWorldRotation(CharacterRotation);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binds functions to moving and looking actions
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMyCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMyCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateLR"), this, &AMyCharacter::RotateLR);
	PlayerInputComponent->BindAxis(TEXT("RotateUD"), this, &AMyCharacter::RotateUD);

	// Binds functions to other character controlls
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jumps);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyCharacter::Dash);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shoot);
	PlayerInputComponent->BindAction("Grapple", IE_Pressed, this, &AMyCharacter::Grapple);
	PlayerInputComponent->BindAction("Grapple", IE_Released, this, &AMyCharacter::EndGrapple);

}

// Moves forward and back
void AMyCharacter::MoveFB(float Value) {
	if (!IsGrappling) {
		AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
	}
}

// Moves left and right
void AMyCharacter::MoveLR(float Value) {
	if (!IsGrappling) {
		AddMovementInput(-GetActorRightVector(), Value * MoveSpeed);
	}
}

// Looks left and right
void AMyCharacter::RotateLR(float Value) {
	if (!IsGrappling) {
		AddControllerYawInput(Value * RotationSpeed);
	}
}

// Looks up and down
void AMyCharacter::RotateUD(float Value) {
	if (!IsGrappling) {
		AddControllerPitchInput(-(Value * RotationSpeed));
	}
}

// Makes character jump
void AMyCharacter::Jumps() {
	if (GetCharacterMovement()->GravityScale == 1 && !IsGrappling) {
		if (CanJump) {
			if (HasDashedGround) {
				// Boost jump if character dashed on ground
				FVector Direction = GetCharacterMovement()->GetLastInputVector();
				if (GetCharacterMovement()->GetLastInputVector() == FVector::ZeroVector) {
					Direction = GetActorForwardVector();
				}
				LaunchCharacter((GetCharacterMovement()->Velocity) + (Direction * BoostJumpDistance) + ((FVector(0, 0, 1) * JumpHeight)), true, true);
			}
				// Normal jump
			else {
				LaunchCharacter(((GetCharacterMovement()->Velocity) + (FVector(0, 0, 1)) * JumpHeight), true, true);
			}
			CanJump = false;
			CanSecondJump = true;
		}
		// Double jump
		else if (CanSecondJump) {
			LaunchCharacter(((GetCharacterMovement()->Velocity) + (FVector(0, 0, 1)) * JumpHeight), true, true);
			CanSecondJump = false;
		}
	}
}

void AMyCharacter::Dash() {
	if (!HasDashed && !IsGrappling) {
		FVector Dash;
		// Gets dash movement based on input, or forward if not input
		if ((GetCharacterMovement()->Velocity.X != FVector::ZeroVector.X || GetCharacterMovement()->Velocity.Y != FVector::ZeroVector.Y) && GetCharacterMovement()->GetLastInputVector() != FVector::ZeroVector) {
			Dash = GetCharacterMovement()->GetLastInputVector();
		}
		else {
			Dash = GetActorForwardVector();
		}
		// Air dash, teleports character forward
		if (GetCharacterMovement()->IsFalling() && !CanJump) {
			GetCharacterMovement()->StopMovementImmediately();
			DashDirection = Dash;
			AddActorWorldOffset(DashDirection * DashDistance, true, (FHitResult*)nullptr, ETeleportType::None);
		}
		// Ground dash, hops forward
		else {
			Dash.Z += DashHeightGround;
			LaunchCharacter(Dash * DashDistanceGround, true, true);
			HasDashedGround = true;
		}
		HasDashed = true;
		DashTime = DashTimeDefault;
	}
}

void AMyCharacter::Sprint() {
	// Increases max walk speed to make character sprint
	if (GetCharacterMovement()->MaxWalkSpeed = WalkSpeed) {
		if (GetCharacterMovement()->Velocity.X != FVector::ZeroVector.X || GetCharacterMovement()->Velocity.Y != FVector::ZeroVector.Y) {
			GetCharacterMovement()->MaxWalkSpeed += SprintSpeed;
		}
	}
}

void AMyCharacter::Shoot() {
	// Spawns bow projectile in front of character to shoot forward
	if (BowPickedUp) {
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector();
		FVector SpawnRotationVector = PlayerCamera->GetForwardVector() * -1;
		FRotator SpawnRotation = SpawnRotationVector.Rotation();
		auto SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation, &SpawnRotation) != nullptr;

		// Plays bow sound
		UGameplayStatics::PlaySound2D(GetWorld(), ShootSound, 0.4);
	}
}

void AMyCharacter::Grapple()
{
	if (GrapplePickedUp && !Grappled) {
		// Parameters for line trace
		FVector Start = PlayerCamera->GetComponentLocation();
		FVector End = Start + PlayerCamera->GetForwardVector() * 2000;
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		// Traces a line a certain distance forward from the camera to find a collision for the grapple
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams())) {
			auto HitPoint = HitResult.ImpactPoint;

			// Make grapple line visible and connects to hit point
			GrappleLine->SetVisibility(true);
			auto Point = HitPoint;
			auto GrapplePoint = UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), Point);
			GrappleLine->EndLocation = GrapplePoint;

			// Sets direction and character movement settings to move player towards hit point on tick
			GrappleDirection = GetActorLocation() - HitPoint;
			GrappleDirection.Normalize();
			GrappleDirection *= -1;
			GetCharacterMovement()->StopMovementImmediately();
			GetCharacterMovement()->GravityScale = 0;
			IsGrappling = true;
			Grappled = true;

			// Plays grapple sound
			UGameplayStatics::PlaySound2D(GetWorld(), GrappleSound, 0.2);
		}
	}
}

void AMyCharacter::EndGrapple()
{
	// Resets character movement settings and ends grapple movement when button is released
	GetCharacterMovement()->GravityScale = 1;
	IsGrappling = false;
	GrappleFinished = false;
	GrappleLine->SetVisibility(false);
}


