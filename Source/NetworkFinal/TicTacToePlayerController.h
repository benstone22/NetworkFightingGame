// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToePlayerController.generated.h"

UCLASS()
class NETWORKFINAL_API ATicTacToePlayerController : public APlayerController
{
    GENERATED_BODY()

public:

    // Called by client when they click a cell
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerMakeMove(int32 CellIndex);
};