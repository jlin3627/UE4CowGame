// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:

	FHttpModule* Http;
	
	/* The actual HTTP call*/
	UFUNCTION()
	void MyHttpCall();

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	

	

	// Your declarations go below!
	private:
	void HttpConnect();
	
};
