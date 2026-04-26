#include "TicTacToeCell.h"
#include "TicTacToePlayerController.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "InputCoreTypes.h"
ATicTacToeCell::ATicTacToeCell()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    // Create mesh component
    CellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));
    RootComponent = CellMesh;

    // Create click box
    ClickBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickBox"));
    ClickBox->SetupAttachment(RootComponent);
    ClickBox->SetBoxExtent(FVector(50.f, 50.f, 10.f));
}

void ATicTacToeCell::BeginPlay()
{
    Super::BeginPlay();

    GameState = GetWorld()->GetGameState<ATicTacToeGameState>();  


    // Enable click events
    CellMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CellMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    CellMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
    //CellMesh->OnClicked.AddDynamic(this, &ATicTacToeCell::OnCellClicked);
    
    
}

void ATicTacToeCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATicTacToeCell, CellIndex);
    DOREPLIFETIME(ATicTacToeCell, CellState);
}

void ATicTacToeCell::OnCellClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
    ATicTacToePlayerController* PC = Cast<ATicTacToePlayerController>(
        GetWorld()->GetFirstPlayerController()
    );
    if (PC)
    {
        PC->ServerMakeMove(CellIndex);
    }
}
/*void ATicTacToeCell::UpdateVisual(ETicTacToeCell cellState) {
    if (cellState == ETicTacToeCell::X)
    {
        // Set mesh/material for X
        UE_LOG(LogTemp, Warning, TEXT("Updating cell %d visual to X"), CellIndex);
		//this-> = "X";
    }
    else if (cellState == ETicTacToeCell::O)
    {
        // Set mesh/material for O
        UE_LOG(LogTemp, Warning, TEXT("Updating cell %d visual to O"), CellIndex);
    }
    else
    {
        // Set mesh/material for empty
        UE_LOG(LogTemp, Warning, TEXT("Updating cell %d visual to Empty"), CellIndex);
	}
}*/

void ATicTacToeCell::OnRep_CellIndex()
{
    // Nothing needed
}

void ATicTacToeCell::OnRep_CellState()
{
    // Tell Blueprint to update the visual
    UE_LOG(LogTemp, Warning, TEXT("OnRep_CellState called for cell %d, new state: %d"), CellIndex, (int32)CellState);
    
   if (GameState && GameState->Board.IsValidIndex(CellIndex))
    {
        CellState = GameState->Board[CellIndex];
    }
    UpdateVisual(CellState);
}