#include "LobbyPlayerController.h"
#include "LobbyGameState.h"
#include "GameFramework/PlayerState.h"

void ALobbyPlayerController::ServerSendChat_Implementation(const FString& Message)
{
    // Guard against empty or too long messages
    if (Message.IsEmpty() || Message.Len() > 200) return;

    ALobbyGameState* GS = GetWorld()->GetGameState<ALobbyGameState>();
    APlayerState* PS = GetPlayerState<APlayerState>();

    if (GS && PS)
    {
        GS->AddChatMessage(PS->GetPlayerName(), Message);
    }
}