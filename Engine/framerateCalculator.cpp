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

#include <SDL3/SDL.h>
#include "framerateCalculator.h"
#include "../Application.h"

#define DRAWFPS

void calculateFramerate()
{
	// Static variables so they persist across calls

	static float framesPerSecond = 0.0f; // Frames per second
	static float lastTime =
		0.0f; // Helps us determine when one second has passed
	static char strFrameRate[50] = {
		0
	}; // String that stores the FPS (for window title)

	// Get the current time.
	// SDL_GetTicks returns the number of milliseconds since program start.
	// We convert milliseconds to seconds by multiplying with 0.001.
	// 12637 ms -> 12.637 s

	float currentTime = SDL_GetTicks() * 0.001f;

	// Each call to this method in DrawGLscene increments the frame counter
	++framesPerSecond;

	// Has one second passed?
	if (currentTime - lastTime > 1.0f) {
		lastTime = currentTime;

#ifdef DRAWFPS
		// Copy the FPS into the string strFrameRate
		SDL_snprintf(strFrameRate, sizeof(strFrameRate), "FPS: %d",
			     int(framesPerSecond));

		// Finally display the FPS string in the window title bar
		SDL_SetWindowTitle(Application::m_pWindow, strFrameRate);
#endif
		//Application::m_fReciprocalFPS = 1/framesPerSecond;
		// Reset the frame counter to 0
		framesPerSecond = 0.0f;
	}
}
