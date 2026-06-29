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

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Application.h"

SDL_AppResult SDL_AppInit(void **appstate, int, char *[])
{
	Application *app = new Application();
	app->init();
	*appstate = app;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	Application *app = (Application *)appstate;
	return app->handleEvent(event);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	Application *app = (Application *)appstate;
	return app->iterate();
}

void SDL_AppQuit(void *appstate, SDL_AppResult)
{
	Application *app = (Application *)appstate;
	delete app;
}
