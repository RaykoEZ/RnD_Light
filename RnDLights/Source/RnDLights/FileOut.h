// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "DistData.h"
#include "FileOut.generated.h"


UCLASS()
class RNDLIGHTS_API AFileOut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFileOut();
	/// @brief LOD distances for going towards the viewer
	UPROPERTY(BlueprintReadWrite)
	FString m_input;
	/// @brief LOD distances for going towards the viewer
	FString m_path;
	/// @brief LOD distances for going towards the viewer
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString m_fileName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/// @brief convert collected data into csv format, appends to already-existing data if needed
	/// @param [in] _data - raw data to be converted
	UFUNCTION(BlueprintCallable)
	void setInput(const FDistData &_data);
	/// @brief saves converted data into a .csv file
	UFUNCTION(BlueprintCallable)
	void saveToCSV();
	
	
};
