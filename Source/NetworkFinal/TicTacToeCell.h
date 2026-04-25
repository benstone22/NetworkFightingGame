#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeGameState.h"
#include "TicTacToeCell.generated.h"

UCLASS()
class NETWORKFINAL_API ATicTacToeCell : public AActor
{
    GENERATED_BODY()

public:

    ATicTacToeCell();

    // Which cell index this is (0-8)
    UPROPERTY(ReplicatedUsing = OnRep_CellIndex, BlueprintReadWrite, Category = "Cell")
    int32 CellIndex = 0;

    // Current state of this cell
    UPROPERTY(ReplicatedUsing = OnRep_CellState, BlueprintReadWrite, Category = "Cell")
    ETicTacToeCell CellState = ETicTacToeCell::Empty;

    // Called when player clicks this cell
    UFUNCTION()
	void OnCellClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

    // Update visual based on state
    UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
    void UpdateVisual(ETicTacToeCell NewState);

    UFUNCTION()
    void OnRep_CellIndex();

    UFUNCTION()
    void OnRep_CellState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

    virtual void BeginPlay() override;

    // Click detection component
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UBoxComponent* ClickBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UStaticMeshComponent* CellMesh;

    UPROPERTY()
    class ATicTacToeGameState* GameState;
};