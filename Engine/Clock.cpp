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

#include "Clock.h"

Clock::Clock()
{
	m_iPauseTicks = 0;
	m_iPauseStart = 0;
	m_bPaused = false;
	m_bPausedBySuspend = false;
}

Uint32 Clock::getTicks()
{
	if (m_bPaused)
		return m_iPauseStart;
	else
		return (SDL_GetTicks() - m_iPauseTicks);
}

void Clock::startPause()
{
	m_bPaused = true;
	m_iPauseStart = SDL_GetTicks();
	//	printf("startPause | m_iPauseStart: %u \n", m_iPauseStart);
}

void Clock::stopPause()
{
	m_bPaused = false;
	// add the duration of the recent pause to the overall pause time
	//	printf("stopPause | m_iPauseTicks: %u \n", m_iPauseTicks);
	m_iPauseTicks += (SDL_GetTicks() - m_iPauseStart);
	m_bPausedBySuspend = false;
	/*	printf("stopPause | SDL_GetTicks: %u \n", SDL_GetTicks());
	printf("stopPause | m_iPauseStart: %u \n", m_iPauseStart);
	printf("stopPause | m_iPauseTicks: %u \n", m_iPauseTicks);*/
}

void Clock::pauseBySuspend()
{
	m_bPausedBySuspend = true;
	m_bPaused = true;
	m_iPauseStart = SDL_GetTicks();
	//	printf("Suspend | SDL_GetTicks: %u \n",SDL_GetTicks());
}

void Clock::reset()
{
	m_iPauseTicks = 0;
	m_iPauseStart = 0;
}
