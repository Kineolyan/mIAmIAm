/*
 * timer.h
 *
 *  Created on: 4 mars 2012
 *      Author: oliv
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>
#include <stack>

class Timer {
	timespec m_endTime;
	std::stack<timespec> m_checkpoints;

	static timespec diff(const timespec& start, const timespec& end);
	static bool greaterThan(const timespec& lh, const timespec& rh);

public:
	Timer();
	~Timer();

	void start(int seconds);
	void stop();

	void checkpoint();
	bool checkTime();
	bool isOver() const;
	bool isOver(const timespec& time) const;
};

#endif /* TIMER_H_ */
