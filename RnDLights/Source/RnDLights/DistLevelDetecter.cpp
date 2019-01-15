// Fill out your copyright notice in the Description page of Project Settings.

#include "DistLevelDetecter.h"


// Sets default values
ADistLevelDetecter::ADistLevelDetecter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_numLevel = 3;
	m_useSafe = true;
	m_currentLevel = 0;
}

// Called when the game starts or when spawned
void ADistLevelDetecter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADistLevelDetecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADistLevelDetecter::init(const float & _dist0)
{
	
	if(_dist0 > 0.0f)
	{
		
		m_LOD = initDist(_dist0);
		
	}
}


TArray<FVector2D> ADistLevelDetecter::initDist(const float _d0)
{
	TArray<FVector2D> ret;
	
	float diff = _d0;
	if(m_useSafe)
	{
		ret.Reserve(m_numLevel - 1 );
		FVector2D range = FVector2D( _d0 * 2.0f , _d0 * 3.0f);
		ret.Add(range);
		//ret[0].X = _d0 * 2.0f;
		//ret[0].Y = ret[0].X + diff;
	
		for (int i = 1; i < m_numLevel - 1; ++i)
		{
			FVector2D range = FVector2D(ret[i - 1].Y, ret[i - 1].Y * 2.0f);
			ret.Add(range);
			//ret[i].X = ret[i - 1].Y;
			//ret[i].Y = ret[i].X * 2.0f;
			

		}

	}
	else
	{
		TArray<FVector2D> otherRet;
		ret.Reserve(m_numLevel);
		/// initialise Distance Pair 0 for from far to near
		FVector2D rangeFromFar = FVector2D(_d0, _d0 * 3.0f);
		//ret[0].X = _d0;
		//ret[0].Y = (2.0f * ret[0].X) + diff;
		otherRet.Add(rangeFromFar);
		/// initialise Distance Pair 1f or from near to far
		FVector2D rangeFromNear = FVector2D(_d0 * 2.0f, _d0 * 3.0f);	
		ret.Add(rangeFromNear);
		//ret[1].X = _d0 * 2.0f;
		//ret[1].Y = ret[1].X + diff;
		

		for (int i = 1; i < m_numLevel - 1; ++i)
		{
			FVector2D range = FVector2D(ret[i - 1].Y, ret[i - 1].Y * 2.0f);
			ret.Add(range);
			otherRet.Add(range);
			//ret[i].X = ret[i - 1].Y;
			//ret[i].Y = ret[i].X * 2.0f;
			

		}
		m_LODOther = otherRet;
	}

	return ret;
}

TArray<FVector2D> ADistLevelDetecter::getRange()
{
	return m_LOD;
}

int ADistLevelDetecter::getLevel(const float & _dist, const float &_deltaDist)
{
	int ret = 0;
	if(m_useSafe)
	{
		if(_dist < m_LOD[0].X)
		{
			//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"),ret);		
			m_currentLevel = ret;
			return ret;
		}

		for (int i = 0; i < m_LOD.Num(); ++i)
		{
			++ret;
			if (_dist >= m_LOD[i].X && _dist < m_LOD[i].Y)
			{	
				//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"), ret);
				m_currentLevel = ret;
				return ret;
			}
		}
	
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("DeltaDist: %f"), _deltaDist);
		/// if going forward
		if(_deltaDist >= 0.0f)
		{
			if (_dist < m_LOD[0].X)
			{
				//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"),ret);		
				m_currentLevel = ret;
				return ret;
			}

			for (int i = 0; i < m_LOD.Num(); ++i)
			{
				++ret;
				if (_dist >= m_LOD[i].X && _dist < m_LOD[i].Y)
				{
					//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"), ret);
					m_currentLevel = ret;
					return ret;
				}
			}
		}
		else
		{
			/// If coming back right after going forward, keep LOD1 until LOD0 for going back is reach
			if(_dist > m_LODOther[0].X && _dist < m_LOD[0].X)
			{
				return m_currentLevel;
			}
			else if (_dist < m_LODOther[0].X)
			{
				//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"),ret);		
				m_currentLevel = ret;
				return ret;
			}

			for (int i = 0; i < m_LOD.Num(); ++i)
			{
				++ret;
				if (_dist >= m_LOD[i].X && _dist < m_LOD[i].Y)
				{
					//UE_LOG(LogTemp, Warning, TEXT("LOD Level: &d"), ret);
					m_currentLevel = ret;
					return ret;
				}
			}
		}
	}
	return ret;
}