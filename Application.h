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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <SDL3/SDL.h>

struct MIX_Mixer;

#ifdef __APPLE__
#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>
#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>
#endif

using namespace std;

class Clock;
class Game;
class Camera;
class Controller;
class InputManager;
class MapManager;
class TextureManager;
class SoundManager;
class TextDrawer;
class ScreenFader;
class MeshManager;
class Config;
class ApplicationMenu;

class Application {
private:
	// definition of states in which the Application can be.
	enum state { MENU = 0, GAME, GAME_PAUSED, QUIT };
	//the current State the application is in
	int m_iState;
	void render();
	//starts a new Game
	void startNewGame();

	// determines resource and preferences paths
	void initPaths();
	//registers the callback "sleepCallback"  to receive system sleep notifications
	void registerSleepCallBack();
#ifdef __APPLE__
	static void sleepCallBack(void *refCon, io_service_t service,
				  natural_t messageType, void *messageArgument);
#endif

public:
	/* The following Vars are Pointers to Game Classes. By making them static, we can easily access them
		by using Application::m_p........
		*/

	// The reciprocal Value of the FPS. Used for time Based Movement throughout the game
	static float m_fReciprocalFPS;

	ApplicationMenu *m_pMainMenu;
	static Clock *m_pClock;
	static Game *m_pGame;
	static Camera *m_pCamera;
	static MeshManager *m_pMeshManager;
	static TextureManager *m_pTextureManager;
	static TextDrawer *m_pTextDrawer;
	static ScreenFader *m_pScreenFader;
	static MapManager *m_pMapManager;
	static InputManager *m_pInputManager;
	static Config *m_pConfig;
	static SoundManager *m_pSoundManager;

	// this pointer is needed for the static callback function "sleepCallBack"
	static Application *m_pApplication;

	static string m_strResourcePath;
	static string m_strPrefPath;
	static string expandResourcePath(const char *relativePath)
	{
		return m_strResourcePath + relativePath;
	}
	static string expandPrefPath(const char *relativePath)
	{
		return m_strPrefPath + relativePath;
	}

	bool m_bSuspendEvent;

	// Display resolution. These values are read once from config and the used throughout the game
	// (can be discarded, when ingame resolution switching is done)
	static SDL_Window *m_pWindow;
	static SDL_GLContext m_glContext;
	static MIX_Mixer *m_pMixer;
	static int screenWidth;
	static int screenHeight;

	Application();
	~Application();

	void init();
	void run();

	//gets called when pause key was pressed
	void pause();

	//gets called whenever application should be paused
	void startPause();
	void stopPause();

	//sets a state
	void setState(int state);
};

#endif
