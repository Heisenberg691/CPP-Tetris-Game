#include "GameState.h"

GameState::GameState()
{
	m_lines = 0;
	m_speedMultiplier = 1;
	m_isGameResetting = false;
}

GameState::~GameState()
{
}

uint32_t GameState::GetLines()
{
	return m_lines;
}

void GameState::SetLines(uint32_t lines)
{
	m_lines = lines;
}

uint32_t GameState::GetSpeedMultiplier()
{
	return m_speedMultiplier;
}

void GameState::SetSpeedMultiplier(uint32_t speedMult)
{
	m_speedMultiplier = speedMult;
}

bool GameState::IsGameResetting()
{
	return m_isGameResetting;
}

void GameState::SetIsGameResetting(bool isResetting)
{
	m_isGameResetting = isResetting;
}

void GameState::Reset()
{
	m_lines = 0;
	m_speedMultiplier = 1;
}
