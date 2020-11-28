#pragma once

class PerformanceTimer {
public:
	PerformanceTimer();
	~PerformanceTimer();

	void Start();
	double Read();
	unsigned int Stop();

	inline unsigned int GetFrequency() const { return frequency; }

private:
	unsigned int started_at = 0;
	unsigned int stopped_at = 0;

	double frequency;

};