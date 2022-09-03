// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#include "GameInstance.h"

Grid::Grid(GameInstance& gameInstance,sf::Vector2i gridSize,uint32_t blockSize, uint32_t blockPadding,bool render):m_gameInstance(gameInstance)
{
    m_isRendered = render;
    m_gridSize = GridSize(gridSize.x, gridSize.y, blockSize, blockPadding);

    sf::Vector2i xBlockLastCoords(m_gridSize.blockSize, m_gridSize.blockSize);
    m_gridEntities.resize(m_gridSize.x + 1);

    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        m_gridEntities[i].resize(m_gridSize.y + 1);
        m_gridEntities[i][0] = new Block(m_gridSize.blockSize);
        m_gridEntities[i][0]->Shape()->setPosition(xBlockLastCoords.x, xBlockLastCoords.y);

        sf::Vector2i yBlockLastCoords = xBlockLastCoords;

        for (uint32_t j = 0; j < m_gridSize.y; j++) {
            yBlockLastCoords += sf::Vector2i(0.0, m_gridSize.blockSize + m_gridSize.blockPadding);

            m_gridEntities[i][j + 1] = new Block(m_gridSize.blockSize);
            m_gridEntities[i][j + 1]->Shape()->setPosition(yBlockLastCoords.x, yBlockLastCoords.y);

        }
        xBlockLastCoords += sf::Vector2i(m_gridSize.blockSize + m_gridSize.blockPadding, 0.0);
    }

    SetRender(m_isRendered);
}

Grid::~Grid()
{
}

GridSize Grid::GetGridSize()
{
	return m_gridSize;
}

std::vector<std::vector<Block*>> Grid::GetGridEntities()
{
	return m_gridEntities;
}

bool Grid::IsRendered()
{
    return m_isRendered;
}

void Grid::SetRender(bool render)
{
    m_isRendered = render;

    if (render) {
        for (uint32_t i = 0; i < m_gridSize.x; i++) {
            for (uint32_t j = 0; j < m_gridSize.y; j++) {
                m_gameInstance.GetEntityRenderer()->AddEntity(m_gridEntities[i][j]);
            }
        }
        return;
    }


    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        for (uint32_t j = 0; j < m_gridSize.y; j++) {
            m_gameInstance.GetEntityRenderer()->RemoveEntity(m_gridEntities[i][j]);
        }
    }
   
}

void Grid::CheckLines()
{
    std::vector<uint32_t> completedLines = GetCompletedHorizontalLinesIndexes();

    if (completedLines.size() <= 0) {
        return;
    }

    ClearHorizontalLine(completedLines[0]);
    OnClearedHorizontalLine();

    for (uint32_t moveLineIndex = (completedLines[0] - 1); moveLineIndex>0; moveLineIndex--){
        MoveHorizontalLineDown(moveLineIndex);
    }

    CheckLines();

}

bool Grid::AreTetrominoesReachedTop()
{
    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        if (m_gridEntities[i][0]->IsOccupied()) {
            return true;
       }
    }
    return false;
}

void Grid::Clear()
{
    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        for (uint32_t j = 0; j < m_gridSize.y; j++) {
            m_gridEntities[i][j]->SetOccupied(false);
            m_gridEntities[i][j]->SetDefaultColor();
        }
    }
}

std::vector<uint32_t> Grid::GetCompletedHorizontalLinesIndexes()
{
    std::vector<uint32_t> completedLines;

    for (uint32_t i = 0; i < m_gridSize.y; i++) 
    {
        bool isCompleted = true;
        for (uint32_t j = 0; j < m_gridSize.x; j++)
        {
            if (!m_gridEntities[j][i]->IsOccupied()) {
                isCompleted = false;
                break;
            }
        }
        if (isCompleted) {
            completedLines.push_back(i);
        }
    }

    return completedLines;
}

void Grid::ClearHorizontalLine(uint32_t lineIndex)
{
    if (!m_gridEntities[0][lineIndex]) {
        return;
    }

    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        m_gridEntities[i][lineIndex]->SetOccupied(false);
        m_gridEntities[i][lineIndex]->SetDefaultColor();
    }
}

void Grid::MoveHorizontalLineDown(uint32_t lineIndex)
{
    for (uint32_t i = 0; i < m_gridSize.x; i++) {
        Block* upperBlock = m_gridEntities[i][lineIndex];
        Block* lowerBlock = m_gridEntities[i][lineIndex+1];

        lowerBlock->SetOccupied(upperBlock->IsOccupied());
        lowerBlock->Shape()->setColor(upperBlock->Shape()->getColor());
    }
    ClearHorizontalLine(lineIndex);
}

bool Grid::HasEnoughSpaceToSpawnTetromino(TetrominoShapes shape)
{
    sf::Vector2i coords(5, 0);
    bool canSpawn = false;


    while (coords.y<2 && !canSpawn)
    {
        canSpawn = CanSpawnTetrominoAtCoords(coords, shape);
        coords.y++;
    }
   
    return true;
}

bool Grid::CanSpawnTetrominoAtCoords(sf::Vector2i coords, TetrominoShapes shape)
{
    for (uint32_t j = 0; j <= 1; j++) {
        std::vector<sf::Vector2i> offsets = TetrominoUtils::GetShapeBlockOffsets(shape);
        for (uint32_t i = 0; i < offsets.size(); i++) {
            sf::Vector2i blockCoords = coords + offsets[i];
            if (blockCoords.x >= m_gridEntities.size() - 1 || blockCoords.y >= m_gridEntities[0].size() - 1) {
                return false;
            }
            if (m_gridEntities[blockCoords.x][blockCoords.y]->IsOccupied()) {
                return false;
            }
        }
    }
    return true;
}


void Grid::OnClearedHorizontalLine()
{
    uint32_t lines = m_gameInstance.GetScore().GetLines();
    lines++;
    m_gameInstance.GetScore().SetLines(lines);
    m_gameInstance.GetScoreboard().SetLines(lines);
    uint32_t xSpeed = (lines / 5);
    if (xSpeed > 1) {
        m_gameInstance.GetScore().SetSpeedMultiplier(xSpeed);
        m_gameInstance.GetScoreboard().SetSpeedMult(xSpeed);
    }
}
