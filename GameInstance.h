// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "EntityRenderer.h"
#include "TextureManager.h"
#include "TetrominoController.h"
#include "Tetromino.h"
#include "GameState.h"
#include "Grid.h"
#include "Block.h"
#include "TetrominoPreviewer.h"
#include "Scoreboard.h"
#include "Score.h"

class GameInstance {

public:
	GameInstance();
	~GameInstance();

	void Init();
	sf::Clock* GetGameTimer();
	TextureManager& GetTextureManager();
	TetrominoController& GetTetrominoController();
	Tetromino* SpawnTetromino(TetrominoShapes tetrominoShape);
	void SetNextTetromino(TetrominoShapes tetrominoShape);
	TetrominoShapes GetRandomTetrominoShape();
	TetrominoShapes GetNextTetrominoShape();
	Grid* GetGrid();
	EntityRenderer* GetEntityRenderer();
	void Reset();
	GameState& GetGameState();
	Score& GetScore();
	TetrominoPreviewer& GetTetrominoPreviewer();
	sf::RenderWindow& GetScreen();
	ScoreBoard& GetScoreboard();
private:
	GameState m_gameState;
	sf::RenderWindow* m_screen;
	EntityRenderer* m_entityRenderer;
	Grid* m_grid;
	sf::Clock* m_gameTimer;
	TextureManager m_texManager;
	TetrominoController m_tetrominoController = TetrominoController(*this);
	TetrominoShapes m_nextTetrominoShape;
	TetrominoPreviewer m_tetrominoPreviewer = TetrominoPreviewer(*this);
	ScoreBoard m_scoreboard = ScoreBoard(*this);
	Score* m_score;
	void GameLoop();
	void UpdateRenderScreen();
	void Update();
	void LoadResources();
};
