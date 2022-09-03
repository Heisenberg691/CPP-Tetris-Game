// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#include "GameInstance.h"
#include "Globals.h"

GameInstance::GameInstance()
{
    m_screen = nullptr;
    m_entityRenderer = nullptr;
    m_grid = nullptr;
    m_gameTimer = new sf::Clock;
    m_nextTetrominoShape = GetRandomTetrominoShape();
}

GameInstance::~GameInstance()
{

}

void GameInstance::Init()
{
	m_screen = new sf::RenderWindow(sf::VideoMode(798, 850), "Tetris");
    m_entityRenderer = new EntityRenderer(m_screen); 
    LoadResources();
    m_grid = new Grid(*this, { GRID_SIZE_X,GRID_SIZE_Y }, BLOCK_SIZE, BLOCK_PADDING, true);
    m_tetrominoPreviewer.SetDisplay(true);
    m_tetrominoPreviewer.DisplayTetromino(GetNextTetrominoShape());
    SpawnTetromino(GetNextTetrominoShape());
    SetNextTetromino(GetRandomTetrominoShape());
    GameLoop();
}

sf::Clock* GameInstance::GetGameTimer()
{
    return m_gameTimer;
}

TextureManager& GameInstance::GetTextureManager()
{
    return m_texManager;
}

TetrominoController& GameInstance::GetTetrominoController()
{
    return m_tetrominoController;
}

Tetromino* GameInstance::SpawnTetromino(TetrominoShapes tetrominoShape)
{
    Tetromino* spawnedTetromino = new Tetromino(*this, tetrominoShape);
    m_tetrominoController.ControlTetromino(spawnedTetromino);

    return spawnedTetromino;
}

void GameInstance::SetNextTetromino(TetrominoShapes tetrominoShape)
{
    m_nextTetrominoShape = tetrominoShape;
    m_tetrominoPreviewer.DisplayTetromino(m_nextTetrominoShape);
}

TetrominoShapes GameInstance::GetRandomTetrominoShape()
{
    srand((unsigned)time(0));
    int rnum = (rand() % 6);
    return TetrominoShapes(rnum);
}

TetrominoShapes GameInstance::GetNextTetrominoShape()
{
    return m_nextTetrominoShape;
}

Grid* GameInstance::GetGrid()
{
    return m_grid;
}

EntityRenderer* GameInstance::GetEntityRenderer()
{
    return m_entityRenderer;
}

void GameInstance::Reset()
{
    if (m_gameState.IsGameResetting()) {
        return;
    }

    m_gameState.SetIsGameResetting(true);
    m_tetrominoController.SetTickEnabled(false);
    if (m_tetrominoController.GetControlledTetromino() != nullptr) {
        m_tetrominoController.GetControlledTetromino()->Destroy();
        m_tetrominoController.ControlTetromino(nullptr);
    }
    m_grid->Clear();
    m_scoreboard.Reset();
    m_gameState.Reset();
    SpawnTetromino(GetNextTetrominoShape());
    SetNextTetromino(GetRandomTetrominoShape());
    m_tetrominoController.SetTickEnabled(true);
    m_gameState.SetIsGameResetting(false);
}

GameState& GameInstance::GetGameState()
{
    return m_gameState;
}

TetrominoPreviewer& GameInstance::GetTetrominoPreviewer()
{
    return m_tetrominoPreviewer;
}

sf::RenderWindow& GameInstance::GetScreen()
{
    return *m_screen;
}

ScoreBoard& GameInstance::GetScoreboard()
{
    return m_scoreboard;
}

void GameInstance::GameLoop()
{

    m_screen->setFramerateLimit(60);
    while (this->m_screen->isOpen())
    {
        sf::Event event;
        while (this->m_screen->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                this->m_screen->close();
                break;
            }
        }

        Update();
    }
}

void GameInstance::UpdateRenderScreen()
{
    m_entityRenderer->SetRenderScreen(m_screen);
}

void GameInstance::Update()
{
    m_screen->clear();
    m_entityRenderer->RenderEntities();
    m_tetrominoController.Tick();
    m_scoreboard.Draw();
    m_screen->display();
}


void GameInstance::LoadResources()
{
   
}
