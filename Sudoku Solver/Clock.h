#pragma once
#include <ctime>

class Clock

{
public:

	class Time

	{
	public:
		Time(double cur_time): time(cur_time)

		{

		}

		double inMicroSeconds()

		{
			return time * 1000.0;
		}

		double inMiliSeconds()

		{
			return time;
		}

		double inSeconds()

		{
			return time / 1000.0;
		}

	private:
		double time;
	};

	Clock()

	{
		prev_time = clock();
	}

	void restart()

	{
		prev_time = clock();
	}

	Time elapsed()

	{
		return Time((double)(clock() - prev_time));
	}
private:
	double prev_time;
};