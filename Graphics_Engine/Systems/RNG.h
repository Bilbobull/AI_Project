// Author: Eric Johnston
#pragma once
#include <chrono>

class RNG {
public:
	int getRandomValue(int max) {
		srand((unsigned)std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		return rand() % max;
	}
};
