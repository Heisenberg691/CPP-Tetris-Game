// This file contains the 'main' function. Program execution begins and ends there.
// Copyright © Veselin Dafchev 2022 All Rights Reserved.

#include "GameInstance.h"

int main()
{
	GameInstance* gameInstance = new GameInstance();
	gameInstance->Init();

	return 0;
}
