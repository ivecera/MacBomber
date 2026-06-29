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

#ifndef CLOCK_H
#define CLOCK_H

#include <SDL3/SDL.h>

class Clock {
private:
	//the total time of ticks the application spent in pause
	Uint32 m_iPauseTicks;

	// used to mesure the duration of the current pause
	Uint32 m_iPauseStart;

	//true if timer is paused
	bool m_bPaused;

	//true if timer was paused by an suspend event
	bool m_bPausedBySuspend;

public:
	Clock();
	//returns SDL_GetTicks() minus m_iPauseTicks
	Uint32 getTicks();

	//get called once when Pause starts/ ends
	void startPause();
	void stopPause();
	// gets called when application pauses because of an suspend event
	void pauseBySuspend();

	//used to set m_iPauseTicks & m_iPauseStart to 0 (needed for a new game)
	void reset();
};

#endif