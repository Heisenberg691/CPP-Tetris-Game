#pragma once
#include <cstdint>

class GameState {
public:
	GameState();
	~GameState();


	uint32_t GetLines();
	void SetLines(uint32_t lines);
	uint32_t GetSpeedMultiplier();
	void SetSpeedMultiplier(uint32_t speedMult);
	bool IsGameResetting();
	void SetIsGameResetting(bool isResetting);
	void Reset();
private:
	uint32_t m_lines;
	uint32_t m_speedMultiplier;
	bool m_isGameResetting;

};
