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

#include "checkScreenResolution.h"
#include "../Application.h"
#include "../Config.h"

bool isResolutionSupported(int resIndex)
{
	bool bSupported = false;
	SDL_Rect **modes;
	// Get all available fullscreen hardware modes
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);

	//check if resolution specified by resIndex is supported
	for (int i = 0; modes[i] != NULL; ++i) {
		//	printf("  %d x %d\n", modes[i]->w, modes[i]->h);

		if ((((int)modes[i]->w) ==
		     Application::m_pConfig->getResolutionWidth(resIndex)) &&
		    (((int)modes[i]->h) ==
		     Application::m_pConfig->getResolutionHeight(resIndex)))
			bSupported = true;
	}

	return bSupported;
}
