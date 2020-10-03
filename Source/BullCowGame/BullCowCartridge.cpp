// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Runtime/Online/HTTP/Public/Http.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Http = &FHttpModule::Get();

    PrintLine(TEXT("Hi there!"));
    PrintLine(TEXT("Print something here and press enter:"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    //ClearScreen();
    FString HiddenWord = TEXT("Test");
    PrintLine(Input);
    if (Input.Equals("Http"))
    {
        PrintLine("Equals");
        HttpConnect();
    }
}

void UBullCowCartridge::HttpConnect()
{
    MyHttpCall();
}

/*Http call*/
void UBullCowCartridge::MyHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UBullCowCartridge::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("https://api.twitter.com/2/tweets?ids=/*Enter tweet ID here*/");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Authorization"), "Bearer /*Enter Bearer code here*/");
	//Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void UBullCowCartridge::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

    PrintLine(Response->GetContentAsString());
	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		FString recievedData = JsonObject->GetStringField("data");

		//Output it to the engine
        PrintLine("Conneted");
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, recievedData);
        PrintLine(recievedData);
	}
}