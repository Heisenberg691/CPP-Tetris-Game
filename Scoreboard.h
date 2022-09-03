#pragma once
#include <SFML/Graphics.hpp>


class GameInstance;

class ScoreBoard {
public:
	ScoreBoard(GameInstance& gameInstance);
	~ScoreBoard();

	void Draw();
	void SetLines(uint32_t lines);
	void SetSpeedMult(uint32_t speedMult);
	void Reset();
private:
	sf::Text m_linesText;
	sf::Text m_speedMultText;
	sf::Font m_font;
	GameInstance& m_gameInstance;

};