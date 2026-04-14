#include "TicTacToeGameState.h"
#include "Net/UnrealNetwork.h"

ATicTacToeGameState::ATicTacToeGameState()
{
    // Initialize empty board with 9 cells
    Board.Init(ETicTacToeCell::Empty, 9);

    // X always goes first
    CurrentTurn = ETicTacToeCell::X;

    bGameOver = false;
    Winner = ETicTacToeCell::Empty;
}

void ATicTacToeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATicTacToeGameState, Board);
    DOREPLIFETIME(ATicTacToeGameState, CurrentTurn);
    DOREPLIFETIME(ATicTacToeGameState, bGameOver);
    DOREPLIFETIME(ATicTacToeGameState, Winner);
}

bool ATicTacToeGameState::MakeMove(int32 CellIndex, ETicTacToeCell Player)
{
    // Validate move
    if (bGameOver) return false;
    if (CellIndex < 0 || CellIndex > 8) return false;
    if (Board[CellIndex] != ETicTacToeCell::Empty) return false;
    if (Player != CurrentTurn) return false;

    // Apply move
    Board[CellIndex] = Player;

    // Check for winner
    ETicTacToeCell Result = CheckWinner();
    if (Result != ETicTacToeCell::Empty)
    {
        bGameOver = true;
        Winner = Result;
    }
    // Check for draw
    else
    {
        bool bDraw = true;
        for (ETicTacToeCell Cell : Board)
        {
            if (Cell == ETicTacToeCell::Empty)
            {
                bDraw = false;
                break;
            }
        }
        if (bDraw)
        {
            bGameOver = true;
            Winner = ETicTacToeCell::Empty;
        }
    }

    // Switch turns
    if (!bGameOver)
    {
        CurrentTurn = (CurrentTurn == ETicTacToeCell::X) 
            ? ETicTacToeCell::O 
            : ETicTacToeCell::X;
    }

    return true;
}

ETicTacToeCell ATicTacToeGameState::CheckWinner()
{
    // All winning combinations
    const int32 WinPatterns[8][3] = {
        {0, 1, 2}, // top row
        {3, 4, 5}, // middle row
        {6, 7, 8}, // bottom row
        {0, 3, 6}, // left column
        {1, 4, 7}, // middle column
        {2, 5, 8}, // right column
        {0, 4, 8}, // diagonal
        {2, 4, 6}  // diagonal
    };

    for (const auto& Pattern : WinPatterns)
    {
        ETicTacToeCell A = Board[Pattern[0]];
        ETicTacToeCell B = Board[Pattern[1]];
        ETicTacToeCell C = Board[Pattern[2]];

        if (A != ETicTacToeCell::Empty && A == B && B == C)
        {
            return A;
        }
    }

    return ETicTacToeCell::Empty;
}
void ATicTacToeGameState::OnRep_Board()
{
    OnBoardUpdated();
}


void ATicTacToeGameState::OnRep_CurrentTurn()
{
    // Blueprint will handle UI update
}

void ATicTacToeGameState::OnRep_bGameOver()
{
    // Blueprint will handle UI update
}

void ATicTacToeGameState::OnRep_Winner()
{
    // Blueprint will handle UI update
}