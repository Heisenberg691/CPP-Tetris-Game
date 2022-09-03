// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include "Block.h"
#include <random>

class GameInstance;

enum class TetrominoShapes {
	SHAPE_I,
	SHAPE_O,
	SHAPE_T,
	SHAPE_S,
	SHAPE_Z,
	SHAPE_J,
	SHAPE_L
};

class Tetromino {
public:
	Tetromino(GameInstance& gameInstance, TetrominoShapes tetrominoShape);
	~Tetromino();

	void Rotate();
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void SetCoordsWithDefaultShape(sf::Vector2i coords);
	void SetCoordsByOffset(sf::Vector2i offset);
	void SetColor(sf::Color color);
	void SetRandomColor();
	bool CanGotoCoordsDefaultRotation(sf::Vector2i coords);
	bool CanRotate();
	bool CanGotoOffsetCoords(sf::Vector2i offset);
	std::vector<sf::Vector2i> GetBlockPositionsForNextRotation();
	void Destroy();
	std::vector<sf::Vector2i> GetBlockPositions();
	sf::Color GetColor();
private:
	GameInstance& m_gameInstance;
	TetrominoShapes m_shapeType = TetrominoShapes::SHAPE_T;
	std::vector<sf::Vector2i> m_blockPositions;
	sf::Color m_color;

};

namespace TetrominoUtils {
	static std::map<TetrominoShapes, std::vector<sf::Vector2i>> m_shapeOffsets{
		{
		 TetrominoShapes::SHAPE_I,
			{
				{ 0, 0 },
				{ 1, 0 },
				{ 2, 0 },
				{ 3, 0 },
			},
		},
		{
		 TetrominoShapes::SHAPE_J,
			{
				{ 0, 0},
				{ 1, 0},
				{ -1, -1},
				{ -1, 0},
			},
		},
		{
		 TetrominoShapes::SHAPE_L,
			{
				{ 0, 0},
				{ 0, 1},
				{ 1, 0},
				{ 2, 0},
			},
		},
		{
		 TetrominoShapes::SHAPE_S,
			{
				{ 0, 0},
				{ 1, 0},
				{ 0, 1},
				{ -1, 1},
			},


		},
		{
		 TetrominoShapes::SHAPE_Z,
			{
				{ 0, 0},
				{ 1, 0},
				{ 1, 1},
				{ 2, 1},
			},


		},
		{
		 TetrominoShapes::SHAPE_T,
			{
				{ 0, 0},
				{ 0, 1},
				{ -1, 0},
				{ 1, 0},
			},

		},
		{
		 TetrominoShapes::SHAPE_O,
			{
				{ 0, 0},
				{ 1, 0},
				{ 0, 1},
				{ 1, 1},
			},

		},
	};

	std::vector<sf::Vector2i> GetShapeBlockOffsets(TetrominoShapes tetrominoShape);
}