#include "LobbyPlayerController.h"
#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"
#include "LobbyGameState.h"
#include "GameFramework/PlayerState.h"

void ALobbyPlayerController::ServerSendChat_Implementation(const FString&Message)
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

void ALobbyPlayerController::ServerSetReady_Implementation(bool bReady)
{
    ALobbyPlayerState* PS = GetPlayerState<ALobbyPlayerState>();
    if (!PS) return;

    PS->bIsReady = bReady;
    UE_LOG(LogTemp, Log, TEXT("ServerSetReady on controller for %s: bIsReady=%d"), *PS->GetPlayerName(), bReady);

    if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>())
    {
        GM->CheckStartConditions();
    }
}
