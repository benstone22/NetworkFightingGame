#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class NETWORKFINAL_API ALobbyGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    ALobbyGameMode();

    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;

    // Check if both players are ready to start
    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void CheckStartConditions();

private:

    // Assign a role to a newly joined player
    void AssignRole(class ALobbyPlayerState* PS);
};