/*
 * timer.h
 *
 *  Created on: 4 mars 2012
 *      Author: oliv
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <environnement.h>
#include <stack>

#ifdef __WINDOWS__

class Timer {
public:
	typedef __int64 time;

private:
	time m_endTime;
	std::stack<time> m_checkpoints;

	bool isOver(const time& time) const;

public:
	Timer();
	~Timer();

	void start(int seconds);
	void stop();

	void checkpoint();
	bool checkTime();
	bool isOver() const;
};

#else
#include <ctime>

class Timer {
	timespec m_endTime;
	std::stack<timespec> m_checkpoints;

	static timespec diff(const timespec& start, const timespec& end);
	static bool greaterThan(const timespec& lh, const timespec& rh);

	bool isOver(const timespec& time) const;

public:
	Timer();
	~Timer();

	void start(int seconds);
	void stop();

	void checkpoint();
	bool checkTime();
	bool isOver() const;
};

#endif /* __WINDOWS__ */

#endif /* TIMER_H_ */
