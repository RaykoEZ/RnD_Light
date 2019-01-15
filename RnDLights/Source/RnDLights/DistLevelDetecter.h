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
	/// safe for using constant LOD distances, false for using bi-directional LOD distances
	UPROPERTY(EditAnywhere)
	bool m_useSafe;
	/// number of LOD levels
	UPROPERTY()
	int m_numLevel;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// current LOD level
	UPROPERTY()
	int m_currentLevel;
	/// LOD distances for going away from the viewer
	UPROPERTY()
	TArray<FVector2D> m_LOD;
	/// LOD distances for going towards the viewer
	UPROPERTY()
	TArray<FVector2D> m_LODOther;
	/// generate LOD distances 
	UFUNCTION()
	TArray<FVector2D> initDist(const float _d0);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/// initialise detector with d0 
	UFUNCTION(BlueprintCallable)
	void init(const float &_dist0);
	/// Gets actual LOD distances
	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> getRange();
	/// called per tick, gets current LOD level
	UFUNCTION(BlueprintCallable)
	int getLevel(const float &_dist, const float &_deltaDist);
};
