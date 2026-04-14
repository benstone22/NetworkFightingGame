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

    // Enable click events
    CellMesh->OnClicked.AddDynamic(this, &ATicTacToeCell::OnCellClicked);
    CellMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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

void ATicTacToeCell::OnRep_CellIndex()
{
    // Nothing needed
}

void ATicTacToeCell::OnRep_CellState()
{
    // Tell Blueprint to update the visual
    UpdateVisual(CellState);
}