// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerState.h" 
#include "TicTacToePlayerController.generated.h"

UCLASS()
class NETWORKFINAL_API ATicTacToePlayerController : public APlayerController
{
    GENERATED_BODY()

public:

    UPROPERTY()
    ELobbyRole PendingRole = ELobbyRole::Spectator;

    // Called by client when they click a cell
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerMakeMove(int32 CellIndex);

    UFUNCTION(Client, Reliable)
void ClientGameOver(ETicTacToeCell Winner);

UFUNCTION(Server, Reliable)
void ServerReturnToLobby();
};