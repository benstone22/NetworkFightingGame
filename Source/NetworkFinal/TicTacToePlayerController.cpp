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