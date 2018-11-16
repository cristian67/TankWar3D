// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectil.h"
#include "Engine/World.h"

// Sets default values
AProjectil::AProjectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
}

void AProjectil::LanzarProjectil(float Speed) {

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	
}

