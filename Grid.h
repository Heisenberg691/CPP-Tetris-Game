// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Tetromino.h"

class GameInstance;

struct GridSize {
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t blockSize = 0;
	uint32_t blockPadding = 0;

	GridSize() {};
	GridSize(uint32_t x, uint32_t y, uint32_t blockSize, uint32_t blockPadding) {
		this->x = x;
		this->y = y;
		this->blockSize = blockSize;
		this->blockPadding = blockPadding;
	};
};

class Grid {
public:
	Grid(GameInstance& gameInstance,sf::Vector2i gridSize, uint32_t blockSize, uint32_t blockPadding,bool render);
	~Grid();

	GridSize GetGridSize();
	std::vector<std::vector<Block*>> GetGridEntities();
	bool IsRendered();
	void SetRender(bool render);
	void CheckLines();
	bool AreTetrominoesReachedTop();
	void Clear();
	std::vector<uint32_t> GetCompletedHorizontalLinesIndexes();
	void ClearHorizontalLine(uint32_t lineIndex);
	void MoveHorizontalLineDown(uint32_t lineIndex);
	bool HasEnoughSpaceToSpawnTetromino(TetrominoShapes shape);
	bool CanSpawnTetrominoAtCoords(sf::Vector2i coords, TetrominoShapes shape);
private:
	void OnClearedHorizontalLine();
	GridSize m_gridSize;
	std::vector<std::vector<Block*>> m_gridEntities;
	GameInstance& m_gameInstance;
	bool m_isRendered;
};