// Fill out your copyright notice in the Description page of Project Settings.

#include "FileOut.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
// Sets default values
AFileOut::AFileOut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_path = FPaths::ProjectContentDir() + "/Data/";
	m_fileName = "distData.csv";
}

void AFileOut::setInput(const FDistData &_data)
{
	/// setup file content
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if (File.CreateDirectoryTree(*m_path))
	{
		FString AbsoluteFilePath = m_path + "/" + m_fileName;
		bool append = File.FileExists(*AbsoluteFilePath);

		auto size_0 = _data.m_seeShad.Num();
		auto size_1 = _data.m_seeLight.Num();
		FString field0 = "1st Visual Change:,";
		FString field1 = "2nd Visual Change:,";

		/// if file doesn't need to be appended, do the normal file initiation
		if (!append)
		{
			UE_LOG(LogTemp, Warning, TEXT("CREATING NEW FILE"));
			m_input += "Start of file:\n";
			m_input += field0;
			/// Insert for field 0
			for (int i = 0; i < size_0; ++i)
			{
				if (i == size_0 - 1)
				{
					m_input += FString::SanitizeFloat(_data.m_seeShad[i]) + ",\n";
				}
				else
				{
					m_input += FString::SanitizeFloat(_data.m_seeShad[i]) + ',';
				}
			}

			m_input += field1;

			/// Insert for field 1
			for (int i = 0; i < size_1; ++i)
			{
				if (i == size_1 - 1)
				{
					m_input += FString::SanitizeFloat(_data.m_seeLight[i]) + ",\n";
				}
				else
				{
					m_input += FString::SanitizeFloat(_data.m_seeLight[i]) + ',';
				}
			}
			m_input += "End of file";
		}
		else
		{
			
			/// This case is for if file already exists-----------------------------------------
			UE_LOG(LogTemp, Warning, TEXT("FILE ALREADY EXISTS, APPENDING..."));

			///reset input string during the same session
			m_input = "";
			/// get offset for appending
			int field0_offset = field0.Len();
			int field1_offset = field1.Len();
			/// original file to be modified
			FString old;
			TUniquePtr<const TCHAR*> path = MakeUnique<const TCHAR*>(*AbsoluteFilePath);
			FFileHelper::LoadFileToString(old,*path.Get());
			int field0Start = old.Find(field0);
			///check for error in file data fields
			if (field0Start == -1)
			{
				UE_LOG(LogTemp, Warning, TEXT("DATA FIELD0 NOT FOUND, PLEASE CHECK CSV FIELD NAMES"));
				return;
			}
			/// start inserting data into fields
			for (int i = 0; i < size_0; ++i)
			{
				m_input += FString::SanitizeFloat(_data.m_seeShad[i]) + ',';
			}
			old.InsertAt(field0Start + field0_offset, m_input);
			/// reset input for next field
			m_input = "";
			///--------------------------------------NEXT FIELD---------------------------------------------------
			int field1Start = old.Find(field1);
			/// error check
			if (field0Start == -1)
			{
				UE_LOG(LogTemp, Warning, TEXT("DATA FIELD1 NOT FOUND, PLEASE CHECK CSV FIELD NAMES"));
				return;
			}
			for (int i = 0; i < size_0; ++i)
			{
				m_input += FString::SanitizeFloat(_data.m_seeLight[i]) + ',';
			}
			old.InsertAt(field1Start + field1_offset, m_input);

			/// set input string to be the modified old
			m_input = old;
		}
	}
}

void AFileOut::saveToCSV()
{

	// basic example taken from Rama at: https://wiki.unrealengine.com/File_Management,_Create_Folders,_Delete_Files,_and_More#Read.2FWrite_to_Files
	
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();
	if (File.CreateDirectoryTree(*m_path))
	{
		// Get absolute file path
		FString AbsoluteFilePath = m_path + "/" + m_fileName;

		FFileHelper::SaveStringToFile(m_input, *AbsoluteFilePath);
		UE_LOG(LogTemp, Warning, TEXT("FILE EXPORTED"))
		
	}
	
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

