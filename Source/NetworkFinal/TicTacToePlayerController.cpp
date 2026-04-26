#include "TicTacToePlayerController.h"
#include "TicTacToeGameMode.h"

void ATicTacToePlayerController::ServerMakeMove_Implementation(int32 CellIndex)
{
    // Tell the GameMode to handle this move
    ATicTacToeGameMode* GM = GetWorld()->GetAuthGameMode<ATicTacToeGameMode>();
    if (GM)
    {
        GM->HandleMove(this, CellIndex);
    }
}

void ATicTacToePlayerController::ClientGameOver_Implementation(ETicTacToeCell Winner)
{
    // Display UI widget (Blueprint will show winner)
    // After player clicks "Return to Lobby":
    // ServerReturnToLobby();
	ServerReturnToLobby();
}


void ATicTacToePlayerController::ServerReturnToLobby_Implementation()
{
    GetWorld()->ServerTravel(TEXT("/Game/Levels/Lobby?listen"));
}