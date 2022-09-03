#include "Score.h"

Score::Score()
{
	m_speedMultiplier = 1;
	m_lines = 0;
}

Score::~Score()
{
}

uint32_t Score::GetLines()
{
	return m_lines;
}

void Score::SetLines(uint32_t lines)
{
	m_lines = lines;
}

uint32_t Score::GetSpeedMultiplier()
{
	return m_speedMultiplier;
}

void Score::SetSpeedMultiplier(uint32_t speedMult)
{
	m_speedMultiplier = speedMult;
}
