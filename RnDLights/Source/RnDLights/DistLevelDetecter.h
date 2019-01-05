// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistLevelDetecter.generated.h"




UCLASS()
class RNDLIGHTS_API ADistLevelDetecter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADistLevelDetecter();
	UPROPERTY(EditAnywhere)
	bool m_useSafe;
	UPROPERTY()
	int m_numLevel;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	TArray<FVector2D> m_LODs;
	UFUNCTION()
	TArray<FVector2D> initDist(const float _d0);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void init(const float &_dist0);

	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> getRange();

	UFUNCTION(BlueprintCallable)
	int getLevel(const float &_dist);
};
