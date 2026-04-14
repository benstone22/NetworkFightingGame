#include "TicTacToeGameMode.h"
#include "TicTacToeGameState.h"
#include "LobbyPlayerState.h"
#include "GameFramework/PlayerController.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
    GameStateClass = ATicTacToeGameState::StaticClass();
}

void ATicTacToeGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}
void ATicTacToeGameMode::BeginPlay()
{
    Super::BeginPlay();
    SpawnBoard();
}

void ATicTacToeGameMode::SpawnBoard()
{
    // Only spawn on server
    if (!HasAuthority()) return;

    float CellSize = 120.f;
    float BoardOffset = CellSize; // centers the board

    for (int32 i = 0; i < 9; i++)
    {
        int32 Row = i / 3;
        int32 Col = i % 3;

        FVector Location(
            (Col * CellSize) - BoardOffset,
            (Row * CellSize) - BoardOffset,
            0.f
        );

        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = 
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        ATicTacToeCell* Cell = GetWorld()->SpawnActor<ATicTacToeCell>(
            ATicTacToeCell::StaticClass(), 
            Location, 
            FRotator::ZeroRotator, 
            Params
        );

        if (Cell)
        {
            Cell->CellIndex = i;
            Cells.Add(Cell);
        }
    }
}
void ATicTacToeGameMode::HandleMove(APlayerController* Player, int32 CellIndex)
{
    // Only runs on server
    if (!HasAuthority()) return;

    ATicTacToeGameState* GS = GetGameState<ATicTacToeGameState>();
    if (!GS) return;

    // Get this player's role from LobbyPlayerState
    ALobbyPlayerState* PS = Player->GetPlayerState<ALobbyPlayerState>();
    if (!PS) return;

    // Map role to cell type
    ETicTacToeCell PlayerCell = ETicTacToeCell::Empty;
    if (PS->LobbyRole == ELobbyRole::PlayerX)
        PlayerCell = ETicTacToeCell::X;
    else if (PS->LobbyRole == ELobbyRole::PlayerO)
        PlayerCell = ETicTacToeCell::O;
    else
        return; // spectators can't move

    // Make the move
    GS->MakeMove(CellIndex, PlayerCell);
}