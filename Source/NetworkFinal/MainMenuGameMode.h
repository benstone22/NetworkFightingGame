#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class NETWORKFINAL_API AMainMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    virtual void BeginPlay() override;

    // Set this in Blueprint to your WBP_MainMenu widget
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

private:

    UUserWidget* MainMenuWidget;
};