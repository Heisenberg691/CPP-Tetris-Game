// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include "Entity.h"


class Block: public Entity {
public:
	Block();
	Block(uint32_t blockSize);
	~Block();

	sf::Sprite* Shape();
	bool IsOccupied();
	void SetOccupied(bool isOccupied);
	void Draw(sf::RenderWindow* screen);
	void SetDefaultColor();
private:
	sf::Sprite* m_shape;
	bool m_isOccupied;

};