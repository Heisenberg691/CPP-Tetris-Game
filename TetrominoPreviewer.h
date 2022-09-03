#pragma once
#include <vector>
#include "Tetromino.h"

class Entity;

class TetrominoPreviewer {
public:

	TetrominoPreviewer(GameInstance& gameInstance);
	~TetrominoPreviewer();


	void SetDisplay(bool display);
	bool IsDisplayed();
	void DisplayTetromino(TetrominoShapes tetromino);
	void SetCoords(sf::Vector2f coords);
private:
	GameInstance& m_gameInstance;
	bool m_isDisplayed;
	Entity* m_frame1;
	Entity* m_frame2;
	std::vector<Block*> m_tetrominoBlocks;
	sf::Vector2f m_coords = { 600.0, 200.0 };
	TetrominoShapes m_currentTetromino;
	int32_t m_size = 260;
};