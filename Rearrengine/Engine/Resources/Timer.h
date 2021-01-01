#pragma once

class Timer {
public:
	Timer();
	~Timer();

	void Start();
	unsigned int Read();
	unsigned int GetTicks();
	unsigned int Stop();

	unsigned int stopped_at = 0;
	unsigned int started_at = 0;
};