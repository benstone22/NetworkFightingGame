// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"


UENUM(BlueprintType)
enum class ELobbyRole : uint8
{
	Unassigned UMETA(DisplayName = "Unassigned"),
	PlayerX UMETA(DisplayName = "Player X"),
	PlayerO UMETA(DisplayName = "Player O"),
	Spectator UMETA(DisplayName = "Spectator")
};

UCLASS()
class NETWORKFINAL_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// Is this player ready to start?
    UPROPERTY(ReplicatedUsing = OnRep_bIsReady, BlueprintReadOnly, Category = "Lobby")
    bool bIsReady = false;

    // This player's role in the game
    UPROPERTY(ReplicatedUsing = OnRep_LobbyRole, BlueprintReadOnly, Category = "Lobby")
    ELobbyRole LobbyRole = ELobbyRole::Unassigned;

    // Called by client to tell server they are ready
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetReady(bool bReady);

    // Called when bIsReady changes on clients
    UFUNCTION()
    void OnRep_bIsReady();

    // Called when Role changes on clients
    UFUNCTION()
    void OnRep_LobbyRole();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
