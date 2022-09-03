#include <SFML/Graphics.hpp>
#include "GameInstance.h"

// Copyright © Veselin Dafchev 2022 All Rights Reserved.

TetrominoController::TetrominoController(GameInstance& gameinstance):m_gameInstance(gameinstance)
{
	m_ControlledTetromino = nullptr;
    m_canRotate = true;
    m_lastMovedDownTime = 0;
    m_lastMovementTime = 0;
    m_isTickEnabled = true;
}

TetrominoController::~TetrominoController()
{
}

Tetromino* TetrominoController::GetControlledTetromino()
{
	return m_ControlledTetromino;
}

void TetrominoController::ControlTetromino(Tetromino* tetromino)
{
	m_ControlledTetromino = tetromino;
}

void TetrominoController::Tick()
{
    if (m_ControlledTetromino == nullptr || !m_isTickEnabled) {
        return;
    }
    float moveDownUpdateInterval = (1000.0 / m_gameInstance.GetGameState().GetSpeedMultiplier());

    if (moveDownUpdateInterval > 100.0) {
        bool moveFast = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        if (moveFast) {
            moveDownUpdateInterval = 100.0;
        }
    }
  
    float GameElapsedTime = m_gameInstance.GetGameTimer()->getElapsedTime().asMilliseconds();

    if (((GameElapsedTime - m_lastMovedDownTime) >= moveDownUpdateInterval)) {
        m_lastMovedDownTime = GameElapsedTime;
        m_ControlledTetromino->MoveDown();
    }
    
    bool updateMovement = ((GameElapsedTime - m_lastMovementTime) >= 50.0);
    if (!updateMovement) {
        return;
    }
    m_lastMovementTime = GameElapsedTime;
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_canRotate = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_ControlledTetromino->MoveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_ControlledTetromino->MoveRight();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_canRotate) {
        m_canRotate = false;
        m_ControlledTetromino->Rotate();
    }
}

void TetrominoController::OnTetrominoReachedBottomCollision()
{
    if (m_gameInstance.GetGameState().IsGameResetting()) {
        return;
    }
    SetTickEnabled(false);
    auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
    auto TetrominoBlockPositions = m_ControlledTetromino->GetBlockPositions();
    for (uint32_t i = 0; i < TetrominoBlockPositions.size(); i++) {
        mapBlocks[TetrominoBlockPositions[i].x][TetrominoBlockPositions[i].y]->SetOccupied(true);
    }

    m_gameInstance.GetGrid()->CheckLines();

    if (!m_gameInstance.GetGrid()->AreTetrominoesReachedTop() && m_gameInstance.GetGrid()->HasEnoughSpaceToSpawnTetromino(m_gameInstance.GetNextTetrominoShape())) {

        m_gameInstance.SpawnTetromino(m_gameInstance.GetNextTetrominoShape());
        m_gameInstance.SetNextTetromino(m_gameInstance.GetRandomTetrominoShape());
        SetTickEnabled(true);
    }
    else {
        m_gameInstance.Reset();
    }
}

void TetrominoController::SetTickEnabled(bool enabled)
{
    m_isTickEnabled = enabled;
}

bool TetrominoController::IsTickEnabled()
{
    return m_isTickEnabled;
}
