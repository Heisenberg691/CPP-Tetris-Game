#pragma once
#include <cstdint>

class GameState {
public:
	GameState();
	~GameState();

	bool IsGameResetting();
	void SetIsGameResetting(bool isResetting);

private:
	bool m_isGameResetting;

};
