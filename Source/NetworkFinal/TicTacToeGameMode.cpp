#include "TicTacToeGameMode.h"
#include "TicTacToeGameState.h"
#include "LobbyPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
    GameStateClass = ATicTacToeGameState::StaticClass();
    PlayerControllerClass = ATicTacToePlayerController::StaticClass();
    PlayerStateClass = ALobbyPlayerState::StaticClass();
}

void ATicTacToeGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (NewPlayer)
    {
        NewPlayer->bShowMouseCursor = true;
        NewPlayer->bEnableClickEvents = true;
        NewPlayer->bEnableMouseOverEvents = true;
    }
}
void ATicTacToeGameMode::BeginPlay()
{
    Super::BeginPlay();
    SpawnBoard();
    SyncAllCells(); 
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

    UE_LOG(LogTemp, Warning, TEXT("HandleMove called for cell %d"), CellIndex);

    ATicTacToeGameState* GS = GetGameState<ATicTacToeGameState>();
    if (!GS) 
    {
        UE_LOG(LogTemp, Error, TEXT("HandleMove: No GameState!"));
        return;
    }

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

     // Make the move on GameState
    if (GS->MakeMove(CellIndex, PlayerCell))
    {
        // SYNC: Update the cell actor's state
        SyncAllCells(); 

        if (GS->bGameOver)
    {
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            ATicTacToePlayerController* PC = Cast<ATicTacToePlayerController>(It->Get());
            if (PC)
            {
                PC->ClientGameOver(GS->Winner);
            }
        }
    }
    }
}

void ATicTacToeGameMode::SyncAllCells()
{
    ATicTacToeGameState* GS = GetGameState<ATicTacToeGameState>();
    if (!GS) return;

    UE_LOG(LogTemp, Warning, TEXT("SyncAllCells called with %d cells"), Cells.Num());

    for (int32 i = 0; i < Cells.Num(); i++)
    {
        if (Cells[i])
        {
            UE_LOG(LogTemp, Warning, TEXT("Syncing cell %d, new state: %d"), i, (int32)GS->Board[i]);
            Cells[i]->CellState = GS->Board[i];
            // Call UpdateVisual directly on server since OnRep won't fire for the server
            Cells[i]->UpdateVisual(GS->Board[i]);
        }
    }
}