#include "GameInstance.h"

ScoreBoard::ScoreBoard(GameInstance& gameInstance): m_gameInstance(gameInstance)
{
	m_linesText = sf::Text();
	m_speedMultText = sf::Text();
	if (!m_font.loadFromFile("Resources/Fonts/RetroGaming.ttf")) {
		std::cout << "ERROR LOADING FONT FOR SCOREBOARD"<<std::endl;
	}

	m_linesText.setString("LINES: " + std::to_string(0));
	m_linesText.setCharacterSize(50);
	m_linesText.setFillColor(sf::Color::White);
	m_linesText.setFont(m_font);
	sf::Vector2f offsetLines(470.0, 350.0);
	m_linesText.setPosition(m_linesText.getPosition() + offsetLines);

	m_speedMultText.setString("SPEED: x" + std::to_string(1));
	m_speedMultText.setCharacterSize(50);
	m_speedMultText.setFillColor(sf::Color::White);
	m_speedMultText.setFont(m_font);
	sf::Vector2f offsetSpeed(470.0, 450.0);
	m_speedMultText.setPosition(m_speedMultText.getPosition() + offsetSpeed);
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::Draw()
{
	m_gameInstance.GetScreen().draw(m_linesText);
	m_gameInstance.GetScreen().draw(m_speedMultText);
}

void ScoreBoard::SetLines(uint32_t lines)
{
	m_linesText.setString("LINES: " + std::to_string(lines));
}


void ScoreBoard::SetSpeedMult(uint32_t speedMult)
{
	m_speedMultText.setString("SPEED: x" + std::to_string(speedMult));
}

void ScoreBoard::Reset()
{
	SetLines(0);
	SetSpeedMult(1);
}
