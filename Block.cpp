// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#include "GameInstance.h"

Block::Block()
{
	m_shape = new sf::Sprite();
	sf::Texture texture;
	m_shape->setTexture(texture);
	m_shape->setTextureRect({ 1, 0, 1,1 });
	m_shape->setColor(sf::Color(50, 50, 50, 255));
	m_isOccupied = false;
}

Block::Block(uint32_t blockSize)
{
	m_shape = new sf::Sprite();
	sf::Texture texture;
	m_shape->setTexture(texture);
	m_shape->setTextureRect({ (int32_t)blockSize, 0, (int32_t)blockSize,(int32_t)blockSize });
	m_shape->setColor(sf::Color(50, 50, 50, 255));
	m_isOccupied = false;
}


Block::~Block()
{

}

sf::Sprite* Block::Shape()
{
	return m_shape;
}

bool Block::IsOccupied()
{
	return m_isOccupied;
}

void Block::SetOccupied(bool isOccupied)
{
	m_isOccupied = isOccupied;
}

void Block::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

void Block::SetDefaultColor()
{
	m_shape->setColor(sf::Color(50, 50, 50, 255));
}
