#pragma once

#include <chrono>
#include <iostream>

class StopWatch
{
public:
	StopWatch(std::ostream& os = std::cout) : m_os(os)
	{
		m_startPoint = std::chrono::high_resolution_clock::now();
	}

	std::chrono::duration<double> Stop()
	{
		auto endPoint = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::duration<double>>(endPoint - m_startPoint);
	}

	~StopWatch()
	{
		auto endPoint = Stop();
		m_os << endPoint.count() << std::endl;
	}

private:
	std::chrono::high_resolution_clock::time_point m_startPoint;
	std::ostream& m_os;
};
