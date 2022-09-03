#include "GameInstance.h"

TetrominoPreviewer::TetrominoPreviewer(GameInstance& gameInstance): m_gameInstance(gameInstance)
{
	m_isDisplayed = false;
	sf::Texture texture;
	m_currentTetromino = TetrominoShapes::SHAPE_O;

	m_frame1 = new Entity();
	m_frame1->Shape()->setColor(sf::Color::White);
	m_frame1->Shape()->setTexture(texture);
	m_frame1->Shape()->setTextureRect({ m_size, 0, m_size, m_size });
	m_frame1->Shape()->setPosition(m_coords);
	m_frame1->Shape()->setOrigin(m_size /2, m_size /2);

	int32_t frame2Size = m_size - 20;

	m_frame2 = new Entity();
	m_frame2->Shape()->setColor(sf::Color::Black);
	m_frame2->Shape()->setTexture(texture);
	m_frame2->Shape()->setTextureRect({ frame2Size, 0, frame2Size,frame2Size });
	m_frame2->Shape()->setPosition(m_coords);
	m_frame2->Shape()->setOrigin(frame2Size / 2, frame2Size / 2);
	m_tetrominoBlocks.resize(4);

	int  blockSize = m_size / 7;
	for (uint32_t i = 0; i < 4; i++)
	{
		m_tetrominoBlocks[i] = new Block(m_gameInstance);
		m_tetrominoBlocks[i]->Shape()->setOrigin(blockSize / 2, blockSize / 2);
		m_tetrominoBlocks[i]->Shape()->setPosition(m_coords);
		m_tetrominoBlocks[i]->Shape()->setTextureRect({ blockSize,0,blockSize ,blockSize });
		m_tetrominoBlocks[i]->Shape()->setColor(sf::Color::Cyan);
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
