#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TicTacToeGameState.h"
#include "TicTacToeCell.h"
#include "TicTacToePlayerController.h"
#include "TicTacToeGameMode.generated.h"
UCLASS()
class NETWORKFINAL_API ATicTacToeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    ATicTacToeGameMode();

    virtual void PostLogin(APlayerController* NewPlayer) override;

    // Called by PlayerController when a player makes a move
    UFUNCTION(BlueprintCallable, Category = "TicTacToe")
    void HandleMove(APlayerController* Player, int32 CellIndex);
    virtual void BeginPlay() override;

private:
    void SpawnBoard();
    void SyncAllCells();

    UPROPERTY()
    ATicTacToePlayerController* PlayerXController = nullptr;

    UPROPERTY()
    ATicTacToePlayerController* PlayerOController = nullptr;

    UPROPERTY()
    TArray<ATicTacToeCell*> Cells;
};