// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY()
		float Throttle;

	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float Time;
};

USTRUCT()
struct FGoKartState
{
	GENERATED_BODY()

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FGoKartMove LastMove;
};

UCLASS()
class KRAZYKARTSUE5_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetAirResistance();
	FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime);

	void UpdateLocationFromVelocity(float DeltaTime);

	// The mass of the car (kg).
	UPROPERTY(EditAnywhere)
		float Mass = 1000;

	// The force applied to the car when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	// Minimum radius of the car turinig circle at full lock (m).
	UPROPERTY(EditAnywhere)
		float MinimumTurningRadius = 10;

	// Higher means more drag.
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;

	// Higher means more rolling resistance.
	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = 0.015;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_MoveForward(float Value);
		void Server_MoveForward_Implementation(float Value);
		bool Server_MoveForward_Validate(float Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_MoveRight(float Value);
		void Server_MoveRight_Implementation(float Value);
		bool Server_MoveRight_Validate(float Value);

	UPROPERTY(Replicated)
		FVector Velocity;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
		FTransform ReplicatedTransform;

	UFUNCTION()
		void OnRep_ReplicatedTransform();

	UPROPERTY(Replicated)
		float Throttle;

	UPROPERTY(Replicated)
		float SteeringThrow;
};