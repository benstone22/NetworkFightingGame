#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

UCLASS()
class NETWORKFINAL_API ALobbyGameState : public AGameStateBase
{
    GENERATED_BODY()

public:

    // Chat log visible to all players
    UPROPERTY(ReplicatedUsing = OnRep_ChatLog, BlueprintReadOnly, Category = "Chat")
    TArray<FString> ChatLog;

    // Add a message to the chat log (call on server only)
    UFUNCTION(BlueprintCallable, Category = "Chat")
    void AddChatMessage(const FString& PlayerName, const FString& Message);

    // Called on clients when ChatLog changes
    UFUNCTION(BlueprintImplementableEvent, Category = "Chat")
    void OnRep_ChatLog();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};