#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"
#include "LobbyGameState.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{
    // Set our custom classes
    PlayerStateClass = ALobbyPlayerState::StaticClass();
    
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ALobbyPlayerState* PS = NewPlayer->GetPlayerState<ALobbyPlayerState>();
    if (PS)
    {
        AssignRole(PS);
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
  Super::Logout(Exiting);

    ALobbyPlayerState* PS = Exiting->GetPlayerState<ALobbyPlayerState>();
    if (PS && PS->LobbyRole == ELobbyRole::PlayerX && !Exiting->IsLocalController())
    {
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PC = It->Get();
            if (PC && PC != Exiting)
            {
                PC->ClientReturnToMainMenuWithTextReason(FText::FromString("Host left the game."));
            }
        }
    }
}

void ALobbyGameMode::AssignRole(ALobbyPlayerState* PS)
{
    bool bXTaken = false;
    bool bOTaken = false;

    for (APlayerState* P : GameState->PlayerArray)
    {
        ALobbyPlayerState* LPS = Cast<ALobbyPlayerState>(P);
        if (!LPS) continue;
        if (LPS->LobbyRole == ELobbyRole::PlayerX) bXTaken = true;
        if (LPS->LobbyRole == ELobbyRole::PlayerO) bOTaken = true;
    }

    if (!bXTaken)
        PS->LobbyRole = ELobbyRole::PlayerX;
    else if (!bOTaken)
        PS->LobbyRole = ELobbyRole::PlayerO;
    else
        PS->LobbyRole = ELobbyRole::Spectator;
}

void ALobbyGameMode::CheckStartConditions()
{
    bool bXReady = false;
    bool bOReady = false;

    if (!GameState)
    {
        UE_LOG(LogTemp, Warning, TEXT("CheckStartConditions: GameState is null"));
        return;
    }

    for (APlayerState* P : GameState->PlayerArray)
    {
        ALobbyPlayerState* LPS = Cast<ALobbyPlayerState>(P);
        if (!LPS) continue;
        if (LPS->LobbyRole == ELobbyRole::PlayerX && LPS->bIsReady) bXReady = true;
        if (LPS->LobbyRole == ELobbyRole::PlayerO && LPS->bIsReady) bOReady = true;
        UE_LOG(LogTemp, Log, TEXT("CheckStartConditions: %s role=%d ready=%d"), *LPS->GetPlayerName(), (int32)LPS->LobbyRole, LPS->bIsReady);
    }

    if (bXReady && bOReady)
    {
        UE_LOG(LogTemp, Log, TEXT("Both players ready, traveling to TicTacToe"));
        
        
        GetWorld()->ServerTravel(TEXT("/Game/Levels/TicTacToe?listen"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Not ready yet: X=%d O=%d"), bXReady, bOReady);
    }
}