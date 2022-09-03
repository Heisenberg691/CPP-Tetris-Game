// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include "Entity.h"

class GameInstance;

enum class BlockColor
{
	DarkBlue,
	Purple,
	Red,
	Green,
	Yellow,
	Blue,
	Orange
};

class Block: public Entity {
public:
	Block(GameInstance& gameInstance);
	~Block();

	sf::Sprite* Shape();
	bool IsOccupied();
	void SetOccupied(bool isOccupied);
	void Draw(sf::RenderWindow* screen);
	void SetDefaultColor();
private:
	sf::Sprite* m_shape;
	GameInstance& m_gameInstance;
	bool m_isOccupied;

};