#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TicTacToeGameState.generated.h"

UENUM(BlueprintType)
enum class ETicTacToeCell : uint8
{
    Empty   UMETA(DisplayName = "Empty"),
    X       UMETA(DisplayName = "X"),
    O       UMETA(DisplayName = "O")
};

UCLASS()
class NETWORKFINAL_API ATicTacToeGameState : public AGameStateBase
{
    GENERATED_BODY()

public:

    ATicTacToeGameState();

    // The 9 cells of the board, replicated to all clients
    UPROPERTY(ReplicatedUsing = OnRep_Board, BlueprintReadOnly, Category = "TicTacToe")
    TArray<ETicTacToeCell> Board;

    // Whose turn is it
    UPROPERTY(ReplicatedUsing = OnRep_CurrentTurn, BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToeCell CurrentTurn;

    // Is the game over
    UPROPERTY(ReplicatedUsing = OnRep_bGameOver, BlueprintReadOnly, Category = "TicTacToe")
    bool bGameOver = false;

    // Who won
    UPROPERTY(ReplicatedUsing = OnRep_Winner, BlueprintReadOnly, Category = "TicTacToe")
    ETicTacToeCell Winner;

    // Make a move on the board (server only)
    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    bool MakeMove(int32 CellIndex, ETicTacToeCell Player);

    // Called when board updates — implement in Blueprint
    UFUNCTION(BlueprintImplementableEvent, Category = "TicTacToe")
    void OnBoardUpdated(); 
    
    // Check if someone won
    ETicTacToeCell CheckWinner();

    // RepNotify functions
    UFUNCTION()
    void OnRep_Board();

    UFUNCTION()
    void OnRep_CurrentTurn();

    UFUNCTION()
    void OnRep_bGameOver();

    UFUNCTION()
    void OnRep_Winner();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};