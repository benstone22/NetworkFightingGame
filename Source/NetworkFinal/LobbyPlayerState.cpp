#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyPlayerState, bIsReady);
    DOREPLIFETIME(ALobbyPlayerState, LobbyRole);
}

void ALobbyPlayerState::ServerSetReady_Implementation(bool bReadyState)
{
    bIsReady = bReadyState;
}

void ALobbyPlayerState::OnRep_bIsReady()
{
    // Blueprint will handle UI update
}

void ALobbyPlayerState::OnRep_LobbyRole()
{
    // Blueprint will handle UI update
}