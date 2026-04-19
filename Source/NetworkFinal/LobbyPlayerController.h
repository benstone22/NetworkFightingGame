#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

UCLASS()
class NETWORKFINAL_API ALobbyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:

    // Called by client to send a chat message to the server
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSendChat(const FString& Message);

    // Called by client to tell server that this player is ready
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetReady(bool bReady);
};
