// Fill out your copyright notice in the Description page of Project Settings.

#include "FileOut.h"


// Sets default values
AFileOut::AFileOut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFileOut::setInput()
{
}

void AFileOut::saveToCSV()
{
}

// Called when the game starts or when spawned
void AFileOut::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFileOut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

