// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

class Tetromino;
class GameInstance;

class TetrominoController {
public:
	TetrominoController(GameInstance& gameinstance);
	~TetrominoController();

	Tetromino* GetControlledTetromino();
	void ControlTetromino(Tetromino* tetromino);
	void Tick();
	void OnTetrominoReachedBottomCollision();
	void SetTickEnabled(bool enabled);
	bool IsTickEnabled();
private:
	Tetromino* m_ControlledTetromino;
	bool m_canRotate;
	uint32_t m_lastMovementTime;
	uint32_t m_lastMovedDownTime;
	GameInstance& m_gameInstance;
	bool m_isTickEnabled;
};