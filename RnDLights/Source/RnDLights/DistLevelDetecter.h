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
	/// @brief safe for using constant LOD distances, false for using bi-directional LOD distances
	UPROPERTY(EditAnywhere)
	bool m_useSafe;
	/// @brief number of LOD levels
	UPROPERTY()
	int m_numLevel;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// @brief current LOD level
	UPROPERTY()
	int m_currentLevel;
	/// @brief LOD distances for going away from the viewer
	UPROPERTY()
	TArray<FVector2D> m_LOD;
	/// @brief LOD distances for going towards the viewer
	UPROPERTY()
	TArray<FVector2D> m_LODOther;
	/// @brief Gets actual LOD distances
	/// @param maximum distance of LOD0 for initialisation
	/// @return distances for LOD ranges 
	UFUNCTION()
	TArray<FVector2D> initDist(const float _d0);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/// @brief initialise detector with d0 
	/// @param maximum distance of LOD0 for initialisation
	UFUNCTION(BlueprintCallable)
	void init(const float &_dist0);
	/// @brief  Gets actual LOD distances
	/// @return LOD distances for one direction only
	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> getRange();
	/// @brief called per tick, gets current LOD level
	/// @param [in] _dist current distance from the viewer
	/// @param [in] _deltaDist change in distance from last frame (direction)
	/// @return current LOD level
	UFUNCTION(BlueprintCallable)
	int getLevel(const float &_dist, const float &_deltaDist);
};
