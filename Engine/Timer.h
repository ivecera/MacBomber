/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL.h>

class Timer {
private:
	// The point in time when the timer alarm triggers
	Uint32 m_iAlarmTime;
	// Time at Timer has been started
	Uint32 m_iStartTime;

public:
	Timer();
	Timer(Uint32 alarm);
	void setAlarm(Uint32 alarmTime);
	// returns true when the alert time has been exceeded
	bool isTimeUp();
	// returns Elapsed Time since Timer Start in ms
	Uint32 getElapsedTime();
};

#endif
