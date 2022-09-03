#include "GameInstance.h"

ScoreBoard::ScoreBoard(GameInstance& gameInstance): m_gameInstance(gameInstance)
{
	m_linesText = new sf::Text();
	m_speedMultText = new sf::Text();

	if (!m_font.loadFromFile("Resources/Fonts/RetroGaming.ttf")) {
		std::cout << "ERROR LOADING FONT FOR SCOREBOARD"<<std::endl;
	}

	auto ConfigurateElements = [&](sf::Text& element, std::string initial_text, sf::Font& font, sf::Vector2f offset) {
		element.setString(initial_text);
		element.setCharacterSize(50);
		element.setFillColor(sf::Color::White);
		element.setFont(font);
		element.setPosition(element.getPosition() + offset);
	};

	ConfigurateElements(*m_linesText, "LINES: 0", m_font, sf::Vector2f(470.0, 350.0));
	ConfigurateElements(*m_speedMultText, "SPEED: x1", m_font, sf::Vector2f(470.0, 450.0));
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::Draw()
{
	m_gameInstance.GetScreen().draw(*m_linesText);
	m_gameInstance.GetScreen().draw(*m_speedMultText);
}

void ScoreBoard::SetLines(uint32_t lines)
{
	m_linesText->setString("LINES: " + std::to_string(lines));
}


void ScoreBoard::SetSpeedMult(uint32_t speedMult)
{
	m_speedMultText->setString("SPEED: x" + std::to_string(speedMult));
}

void ScoreBoard::Reset()
{
	SetLines(0);
	SetSpeedMult(1);
}
