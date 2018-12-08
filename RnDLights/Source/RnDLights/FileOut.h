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
	UPROPERTY(BlueprintReadWrite)
	FString m_input;
	FString m_path;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString m_fileName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void setInput(const FDistData &_data);

	UFUNCTION(BlueprintCallable)
	void saveToCSV();
	
	
};
