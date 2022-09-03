#pragma once
#include <cstdint>

class Score {
public:
	Score();
	~Score();


	uint32_t GetLines();
	void SetLines(uint32_t lines);
	uint32_t GetSpeedMultiplier();
	void SetSpeedMultiplier(uint32_t speedMult);
private:
	uint32_t m_lines;
	uint32_t m_speedMultiplier;

};
