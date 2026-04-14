#include "LobbyGameState.h"
#include "Net/UnrealNetwork.h"

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyGameState, ChatLog);
}

void ALobbyGameState::AddChatMessage(const FString& PlayerName, const FString& Message)
{
    // Only runs on server
    if (!HasAuthority()) return;

    // Sanitize length
    FString Sanitized = Message.Left(200);

    // Add to log
    ChatLog.Add(FString::Printf(TEXT("[%s]: %s"), *PlayerName, *Sanitized));

    // Cap history at 50 messages
    if (ChatLog.Num() > 50)
    {
        ChatLog.RemoveAt(0);
    }
}