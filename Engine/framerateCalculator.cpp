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

#include <SDL.h>
#include "framerateCalculator.h"
#include "../Application.h"

#define DRAWFPS

void calculateFramerate()
{
	// Statische Variablen damit sie persistent sind

	static float framesPerSecond = 0.0f; // Frames pro Sekunde
	static float lastTime =
		0.0f; // Hilft uns zu entscheiden wann eine Sekunde vorbei ist
	static char strFrameRate[50] = {
		0
	}; // String der die FPS speichert ( fuer Fenster )

	// Wir nehmen die aktuelle Zeit.
	// SDL liefert mit SDL_GetTicks die Zahl der Millisekunden seit Programmbeginn
	// Wir wandeln millisekunden in Sekunden um, durch die Multiplikaton mit 0.001
	// 12637 ms -> 12.637 s

	float currentTime = SDL_GetTicks() * 0.001f;

	// Bei jedem Aufruf dieser Methode in DrawGLscene z‰hlen wir ein Frame nach oben
	++framesPerSecond;

	// Ist eine Sekunde vergangen ?
	if (currentTime - lastTime > 1.0f) {
		lastTime = currentTime;

#ifdef DRAWFPS
		// Kopiert die FPS in den String strFrameRate
		sprintf(strFrameRate, "FPS: %d", int(framesPerSecond));

		// Zeige schlieﬂlich den FPS-String in der FensterTitelBar an
		SDL_WM_SetCaption(strFrameRate, "OpenGL. ");
#endif
		//Application::m_fReciprocalFPS = 1/framesPerSecond;
		// Setze den Frame Z‰hler wieder auf 0
		framesPerSecond = 0.0f;
	}
}
