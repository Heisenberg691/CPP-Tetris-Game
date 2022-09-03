// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#include "Globals.h"
#include "GameInstance.h"

Tetromino::Tetromino(GameInstance& gameInstance,TetrominoShapes tetrominoShape) :m_gameInstance(gameInstance)
{
	m_shapeType = tetrominoShape;
	
	m_blockPositions = {
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};
	SetRandomColor();
	sf::Vector2i coords(5, 0);
	while (!CanGotoCoordsDefaultRotation(coords) && coords.y<2) {
		coords.y++;
	}

	SetCoordsWithDefaultShape(coords);
}


Tetromino::~Tetromino()
{

}

void Tetromino::Rotate()
{
	if (!CanRotate()) {
		return;
	}

	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	auto nextBlockPositions = GetBlockPositionsForNextRotation();

	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->SetDefaultColor();
	}

	m_blockPositions = nextBlockPositions;

	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->Shape()->setColor(m_color);
	}

}

void Tetromino::MoveRight()
{
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	auto blockPositions = m_blockPositions;

	uint32_t j = blockPositions[1].y - blockPositions[0].y;

	for (uint32_t i = 1; i < blockPositions.size(); i++) {
		blockPositions[i].y = (blockPositions[0].y + blockPositions[i].x) - blockPositions[0].x;
		blockPositions[i].x = blockPositions[0].x - j;
		if (i >= 3) {
			continue;
		}
		j = blockPositions[i + 1].y - blockPositions[0].y;
	}


	if (!CanGotoOffsetCoords(sf::Vector2i(1, 0))) {
		return;
	}
	SetCoordsByOffset(sf::Vector2i(1, 0));
}

void Tetromino::MoveLeft()
{

	if (!CanGotoOffsetCoords(sf::Vector2i(-1, 0))) {
		return;
	}
	SetCoordsByOffset(sf::Vector2i(-1, 0));
}

void Tetromino::MoveDown()
{

	if (!CanGotoOffsetCoords(sf::Vector2i(0, 1))) {
		m_gameInstance.GetTetrominoController().OnTetrominoReachedBottomCollision();
		return;
	}

	SetCoordsByOffset(sf::Vector2i(0, 1));
}

void Tetromino::SetCoordsWithDefaultShape(sf::Vector2i coords)
{
	std::vector<sf::Vector2i> offsets = TetrominoUtils::GetShapeBlockOffsets(m_shapeType);
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->SetDefaultColor();
		m_blockPositions[i] = coords;
	}

	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		m_blockPositions[i] += offsets[i];
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->Shape()->setColor(m_color);
	}

}

void Tetromino::SetCoordsByOffset(sf::Vector2i offset)
{
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->SetDefaultColor();
	}
	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		m_blockPositions[i] += offset;
		mapBlocks[m_blockPositions[i].x][m_blockPositions[i].y]->Shape()->setColor(m_color);
	}
}

void Tetromino::SetColor(sf::Color color)
{
	m_color = color;
}

void Tetromino::SetRandomColor()
{
	std::vector<sf::Color> colors{
		sf::Color::Blue,
		sf::Color::Cyan,
		sf::Color::Green,
		sf::Color::Red,
		sf::Color::Yellow
	};
	
	srand((unsigned)time(0));
	int rnum = (rand() % 5);
	SetColor(colors[rnum]);
}

bool Tetromino::CanGotoCoordsDefaultRotation(sf::Vector2i coords)
{
	if (coords.x < 0 || coords.y < 0) {
		return false;
	}

	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	if (coords.x >= mapBlocks.size()-1 || coords.y >= mapBlocks[0].size()-1) {
		return false;
	}
	std::vector<sf::Vector2i> offsets = TetrominoUtils::GetShapeBlockOffsets(m_shapeType);
	for (uint32_t i = 0; i < offsets.size(); i++) {
		sf::Vector2i blockCoords = coords + offsets[i];

		//std::cout << "X = " << blockCoords.x << " Y = " << blockCoords.y << " INDEX " << i << std::endl;
		if (blockCoords.x >= mapBlocks.size()-1 || blockCoords.y >= mapBlocks[0].size()-1) {
			return false;
		}
		if (mapBlocks[blockCoords.x][blockCoords.y]->IsOccupied()) {
			return false;
		}
	}
	return true;
	
}
bool Tetromino::CanRotate()
{
	if (m_shapeType == TetrominoShapes::SHAPE_O) {
		return false;
	}
	auto nextBlockPositions = GetBlockPositionsForNextRotation();
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();

	for (uint32_t i = 0; i < nextBlockPositions.size(); i++) {
		if (nextBlockPositions[i].x < 0 || nextBlockPositions[i].y < 0) {
			return false;
		}
		if (nextBlockPositions[i].x >= mapBlocks.size() - 1 || nextBlockPositions[i].y >= mapBlocks[0].size() - 1) {
			return false;
		}
		if (mapBlocks[nextBlockPositions[i].x][nextBlockPositions[i].y]->IsOccupied()) {
			return false;
		}
	}
	return true;

}
bool Tetromino::CanGotoOffsetCoords(sf::Vector2i offset)
{
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	for (uint32_t i = 0; i < m_blockPositions.size(); i++) {
		auto nextBlockPos = m_blockPositions[i] + offset;

		if (nextBlockPos.x < 0 || nextBlockPos.y < 0) {
			return false;
		}
		if (nextBlockPos.x >= mapBlocks.size() - 1 || nextBlockPos.y >= mapBlocks[0].size() - 1) {
			return false;
		}
		if (mapBlocks[nextBlockPos.x][nextBlockPos.y]->IsOccupied())
		{
			return false;
		}
	}

	return true;
}
std::vector<sf::Vector2i> Tetromino::GetBlockPositionsForNextRotation()
{
	static auto mapBlocks = m_gameInstance.GetGrid()->GetGridEntities();
	auto blockPositions = m_blockPositions;

	uint32_t j = blockPositions[1].y - blockPositions[0].y;

	for (uint32_t i = 1; i < blockPositions.size(); i++) {
		blockPositions[i].y = (blockPositions[0].y + blockPositions[i].x) - blockPositions[0].x;
		blockPositions[i].x = blockPositions[0].x - j;
		if (i >= 3) {
			continue;
		}
		j = blockPositions[i + 1].y - blockPositions[0].y;
	}

	return blockPositions;
}
void Tetromino::Destroy()
{
	delete this;
}
std::vector<sf::Vector2i> Tetromino::GetBlockPositions()
{
	return m_blockPositions;
}


sf::Color Tetromino::GetColor()
{
	return m_color;
}

std::vector<sf::Vector2i> TetrominoUtils::GetShapeBlockOffsets(TetrominoShapes tetrominoShape)
{
	return m_shapeOffsets[tetrominoShape];
}
