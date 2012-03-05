/*
 * timer.cpp
 *
 *  Created on: 4 mars 2012
 *      Author: oliv
 */

#include "timer.h"

using namespace std;

#ifdef __WINDOWS__
#include <Windows.h>

Timer::Timer():
	m_endTime(),
	m_checkpoints()
{}

Timer::~Timer()
{}

void Timer::start(int seconds) {
	if (!m_checkpoints.empty()) {
		stop();
	}

	m_endTime = timeGetTime() + 1000 * seconds;
}

/**
 * Vide le stack de checkpoints pour pouvoir relancer le compteur
 */
void Timer::stop() {
	while (!m_checkpoints.empty()) {
		m_checkpoints.pop();
	}
}

/**
 * Ajoute un checkpoint
 */
void Timer::checkpoint() {
	m_checkpoints.push(timeGetTime());
}

/**
 * Vérifie qu'il reste assez de temps pour effectuer la même opération
 * que précédement
 */
bool Timer::checkTime() {
	time lastCheckpoint = m_checkpoints.top(), 
		currentTime = timeGetTime();

	if (isOver(currentTime)) {
		return false;
	}

	return m_endTime + lastCheckpoint >= 2*currentTime;
}

bool Timer::isOver() const {
	return timeGetTime() >= m_endTime;
}

bool Timer::isOver(const time& t) const {
	return t >= m_endTime;
}

#else

Timer::Timer():
	m_endTime(),
	m_checkpoints()
{}

Timer::~Timer()
{}

void Timer::start(int seconds) {
	if (!m_checkpoints.empty()) {
		stop();
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_endTime);
	m_endTime.tv_sec+= seconds;
}

/**
 * Vide le stack de checkpoints pour pouvoir relancer le compteur
 */
void Timer::stop() {
	while (!m_checkpoints.empty()) {
		m_checkpoints.pop();
	}
}

/**
 * Ajoute un checkpoint
 */
void Timer::checkpoint() {
	timespec newTime;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &newTime);
	m_checkpoints.push(newTime);
}

/**
 * Vérifie qu'il reste assez de temps pour effectuer la même opération
 * que précédement
 */
bool Timer::checkTime() {
	timespec lastCheckpoint = m_checkpoints.top(), currentTime;
	m_checkpoints.pop();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);

	if (isOver(currentTime)) {
		return false;
	}

	return greaterThan(diff(m_endTime, currentTime),
			diff(currentTime, lastCheckpoint));
}

bool Timer::isOver() const {
	timespec currentTime;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);

	return greaterThan(currentTime, m_endTime);
}

bool Timer::isOver(const timespec& time) const {
	return greaterThan(time, m_endTime);
}

bool Timer::greaterThan(const timespec& lh, const timespec& rh) {
	if (lh.tv_sec > rh.tv_sec) {
		return true;
	}
	else if (lh.tv_sec == rh.tv_sec
			&& lh.tv_nsec >= rh.tv_nsec) {
		return true;
	}
	else {
		return false;
	}
}

timespec Timer::diff(const timespec& start, const timespec& end) {
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
	else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}

	return temp;
}

#endif /* __WINDOWS__ */