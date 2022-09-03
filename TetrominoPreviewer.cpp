#include "GameInstance.h"

TetrominoPreviewer::TetrominoPreviewer(GameInstance& gameInstance): m_gameInstance(gameInstance)
{
	m_isDisplayed = false;
	sf::Texture texture;
	m_currentTetromino = TetrominoShapes::SHAPE_O;

	auto ConfigurateElement= [](Entity& frame,sf::Color color, sf::Texture texture, int32_t rectSize, sf::Vector2f coords) {
		frame.Shape()->setColor(color);
		frame.Shape()->setTexture(texture);
		frame.Shape()->setTextureRect({ rectSize, 0, rectSize, rectSize });
		frame.Shape()->setPosition(coords);
		frame.Shape()->setOrigin((float)rectSize / 2, (float)rectSize / 2);
	};


	m_frame1 = new Entity();
	m_frame2 = new Entity();
	int32_t frame2Size = m_size - 20;
	ConfigurateElement(*m_frame1, sf::Color::White, texture, m_size, m_coords);
	ConfigurateElement(*m_frame2, sf::Color::Black, texture, frame2Size, m_coords);

	m_tetrominoBlocks.resize(4);
	int  blockSize = m_size / 7;

	for (uint32_t i = 0; i < 4; i++)
	{
		m_tetrominoBlocks[i] = new Block();
		ConfigurateElement(*m_tetrominoBlocks[i], sf::Color::Cyan, texture, blockSize, m_coords);
	}

}

TetrominoPreviewer::~TetrominoPreviewer()
{
}

void TetrominoPreviewer::SetDisplay(bool display)
{
	if (m_isDisplayed == display) {
		return;
	}

	m_isDisplayed = display;

	if (m_isDisplayed)
	{
		m_gameInstance.GetEntityRenderer()->AddEntity(m_frame1);
		m_gameInstance.GetEntityRenderer()->AddEntity(m_frame2);

		for (uint32_t i = 0; i < m_tetrominoBlocks.size(); i++)
		{
			m_gameInstance.GetEntityRenderer()->AddEntity(m_tetrominoBlocks[i]);
		}
		return;
	}

	m_gameInstance.GetEntityRenderer()->RemoveEntity(m_frame1);
	m_gameInstance.GetEntityRenderer()->RemoveEntity(m_frame2);

	for (uint32_t i = 0; i < m_tetrominoBlocks.size(); i++)
	{
		m_gameInstance.GetEntityRenderer()->RemoveEntity(m_tetrominoBlocks[i]);
	}
}

bool TetrominoPreviewer::IsDisplayed()
{
	return m_isDisplayed;
}

void TetrominoPreviewer::DisplayTetromino(TetrominoShapes tetromino)
{

	auto offsets = TetrominoUtils::GetShapeBlockOffsets(tetromino);

	for (uint32_t i = 0; i < 4; i++)
	{
		sf::Vector2f newPos;
		auto grid = m_gameInstance.GetGrid();
		float blockSize = (m_size / 6);

		if (tetromino == TetrominoShapes::SHAPE_I) {
			offsets[i].x -= 2;
		}

		newPos.x = m_coords.x + (offsets[i].x * blockSize);
		newPos.y = m_coords.y + (offsets[i].y * blockSize);

		
		m_tetrominoBlocks[i]->Shape()->setPosition(newPos);
	}
}

void TetrominoPreviewer::SetCoords(sf::Vector2f coords)
{
	m_coords = coords;

	m_frame1->Shape()->setPosition(m_coords);
	m_frame2->Shape()->setPosition(m_coords);
	for (uint32_t i = 0; i < 4; i++)
	{
		m_tetrominoBlocks[i]->Shape()->setPosition(m_coords);
	}

	DisplayTetromino(m_currentTetromino);
}
