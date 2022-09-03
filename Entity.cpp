// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#include "Entity.h"

Entity::Entity()
{
	m_shape = new sf::Sprite();
}

Entity::~Entity()
{
}

void Entity::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

sf::Sprite* Entity::Shape()
{
	return m_shape;
}