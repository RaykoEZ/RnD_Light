// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistData.generated.h"


/// Struct for data
USTRUCT(BlueprintType)
struct FDistData
{
	GENERATED_BODY()
	
	/// Distance for seeing shady figure/license plate and lights but no colour from vehicle body
	UPROPERTY(BlueprintReadWrite)
		TArray<float> m_seeShad;
	
	/// Distance for seeing lights only
	UPROPERTY(BlueprintReadWrite)
		TArray<float> m_seeLight;

};
