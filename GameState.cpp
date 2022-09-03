#include "GameState.h"

GameState::GameState()
{
	m_isGameResetting = false;
}

GameState::~GameState()
{
}

bool GameState::IsGameResetting()
{
	return m_isGameResetting;
}

void GameState::SetIsGameResetting(bool isResetting)
{
	m_isGameResetting = isResetting;
}
