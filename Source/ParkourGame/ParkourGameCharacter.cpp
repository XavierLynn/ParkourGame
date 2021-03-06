// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParkourGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AParkourGameCharacter

AParkourGameCharacter::AParkourGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	MyAParkourGameCharacter();

}

//////////////////////////////////////////////////////////////////////////
// Input

void AParkourGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AParkourGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AParkourGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AParkourGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AParkourGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AParkourGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AParkourGameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AParkourGameCharacter::OnResetVR);


	//MySetupPlayerInputComponent(PlayerInputComponent);
}



void AParkourGameCharacter::OnResetVR()
{
	// If ParkourGame is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ParkourGame.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AParkourGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AParkourGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AParkourGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AParkourGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AParkourGameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AParkourGameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
//---------------------------------------------------------------------------------------




void AParkourGameCharacter::RightGo()
{
	if (CanTurn)
	{
		FRotator MyRotator = FRotator(0, 90, 0);
		DesireRotaion = CombineRotatot(DesireRotaion, MyRotator);
		Right_State = true;
	}
}

void AParkourGameCharacter::LeftGo()
{
	if (CanTurn)
	{
		FRotator MyRotator = FRotator(0, -90, 0);
		DesireRotaion = CombineRotatot(DesireRotaion, MyRotator);
		Left_State = true;
	}
}



void AParkourGameCharacter::MyAParkourGameCharacter()
{
	bDeath = false;
	Right_State = false;
	Left_State = false;
	CanTurn = true;
	DesireRotaion = FRotator(0);

}

void AParkourGameCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AParkourGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bDeath)
	{
	}
	else
	{
		MoveCanTurn();
		KeepMoving();
	}
}

void AParkourGameCharacter::KeepMoving()
{
	AddMovementInput(JudgeRorL(),1);
}

void AParkourGameCharacter::MoveCanTurn()
{
	//GetController()->SetControlRotation(FMath::RInterpTo(GetControlRotation(), DesireRotaion, GetWorld()->GetRealTimeSeconds(), 10));
	GetController()->SetControlRotation(DesireRotaion);

}

FVector AParkourGameCharacter::JudgeRorL()
{
	if (Right_State)
	{
		Right_State = false;
		return AddInputMoveForWord();
	}
	else if (Left_State)
	{
		Left_State = false;
		return AddInputMoveForWord();
	}
	else
	{
		return AddInputMoveForWord();
	}

}

FVector AParkourGameCharacter::AddInputMoveForWord()
{
	FVector Direction;
	if (Controller != nullptr)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
	}
	return Direction;
}

FRotator AParkourGameCharacter::CombineRotatot(FRotator CurRotator, FRotator NewRotator)
{
	FQuat CurQuat = FQuat(CurRotator);
	FQuat NewQuat = FQuat(NewRotator);
	return FRotator(CurQuat * NewQuat);
}

void AParkourGameCharacter::MySetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("RightGo",IE_Pressed, this, &AParkourGameCharacter::RightGo);
	PlayerInputComponent->BindAction("LeftGo", IE_Pressed, this, &AParkourGameCharacter::LeftGo);
}