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
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL.h>

#include "Application.h"
#include "Config.h"
#include "Gametypes/Game.h"
#include "Gametypes/Game_Standard.h"
#include "Gametypes/Game_MapDestruction.h"

#include "Menu/ApplicationMenu.h"
#include "Engine/Camera.h"
#include "Controller/Controller_Keyboard.h"
#include "Controller/Controller_Joystick.h"

#include "Engine/InputManager.h"

#include "Map/MapManager.h"
#include "Engine/MeshManager.h"
#include "Engine/TextureManager.h"
#include "Engine/SoundManager.h"
#include "Engine/TextDrawer.h"
#include "Engine/ScreenFader.h"
#include "Engine/framerateCalculator.h"
#include "Engine/Init.h"
#include "Engine/Clock.h"

#include "Engine/ortho.h"
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <time.h>

#include "Defines.h"

#define FREECAMERA

Camera *Application::m_pCamera = NULL;
MeshManager *Application::m_pMeshManager = NULL;
TextureManager *Application::m_pTextureManager = NULL;
MapManager *Application::m_pMapManager = NULL;
SoundManager *Application::m_pSoundManager = NULL;
Application *Application::m_pApplication = NULL;
TextDrawer *Application::m_pTextDrawer = NULL;
ScreenFader *Application::m_pScreenFader = NULL;
InputManager *Application::m_pInputManager = NULL;
Config *Application::m_pConfig = NULL;
Clock *Application::m_pClock = NULL;
Game *Application::m_pGame = NULL;
SDL_Window *Application::m_pWindow = NULL;
SDL_GLContext Application::m_glContext = NULL;
MIX_Mixer *Application::m_pMixer = NULL;

float UPDATE_FPS = 30;
Uint32 TICK_TIME = (Uint32)(1000 / UPDATE_FPS); // ( TICK_TIME = 1000/FPS)
int MAX_LOOPS = 2;
float Application::m_fReciprocalFPS = 1 / UPDATE_FPS; //( 1/FPS)
string Application::m_strResourcePath = string();
string Application::m_strPrefPath = string();

int Application::screenWidth = 0;
int Application::screenHeight = 0;

#ifdef __APPLE__
io_connect_t root_port;
#endif

Application::Application()
{
	m_pApplication = this;
	initPaths();
	registerSleepCallBack();
}

Application::~Application()
{
	if (m_pGame != NULL)
		delete m_pGame;

	delete m_pMainMenu;
	delete m_pCamera;
	delete m_pInputManager;
	delete m_pMapManager;
	delete m_pTextureManager;
	delete m_pMeshManager;
	delete m_pSoundManager;
	delete m_pTextDrawer;
	delete m_pScreenFader;
	delete m_pClock;
	delete m_pConfig;
}

void Application::initPaths()
{
	const char *basePath = SDL_GetBasePath();
	if (basePath) {
		m_strResourcePath = basePath;
		// strip trailing path separator — callers supply their own
		if (!m_strResourcePath.empty() &&
		    m_strResourcePath.back() == '/')
			m_strResourcePath.pop_back();
	} else {
		m_strResourcePath = ".";
	}

	char *prefPath = SDL_GetPrefPath("MacBomber", "MacBomber");
	if (prefPath) {
		m_strPrefPath = prefPath;
		SDL_free(prefPath);
	} else {
		m_strPrefPath = m_strResourcePath;
	}
}

void Application::registerSleepCallBack()
{
#ifdef __APPLE__
	IONotificationPortRef
		notifyPortRef; // notification port allocated by IORegisterForSystemPower
	io_object_t notifierObject; // notifier object, used to deregister later
	void *refCon = NULL; // this parameter is passed to the callback

	// register to receive system sleep notifications
	root_port = IORegisterForSystemPower(refCon, &notifyPortRef,
					     Application::sleepCallBack,
					     &notifierObject);
	if (root_port == NULL) {
		SDL_Log("IORegisterForSystemPower failed");
	}

	// add the notification port to the application runloop
	CFRunLoopAddSource(CFRunLoopGetCurrent(),
			   IONotificationPortGetRunLoopSource(notifyPortRef),
			   kCFRunLoopCommonModes);

	/*
       Start the run loop to receive sleep notifications.  You don't need to
       call this if you already have a Carbon or Cocoa EventLoop running.
    */
	//   CFRunLoopRun();
#endif
}

#ifdef __APPLE__
void Application::sleepCallBack(void *refCon, io_service_t service,
				natural_t messageType, void *messageArgument)
{
	switch (messageType) {
	case kIOMessageCanSystemSleep:
		/*
               Idle sleep is about to kick in.
               Applications have a chance to prevent sleep by calling IOCancelPowerChange.
               Most applications should not prevent idle sleep.

               Power Management waits up to 30 seconds for you to either allow or deny idle sleep.
               If you don't acknowledge this power change by calling either IOAllowPowerChange
               or IOCancelPowerChange, the system will wait 30 seconds then go to sleep.
            */

		// we will allow idle sleep
		IOAllowPowerChange(root_port, (long)messageArgument);
		break;

	case kIOMessageSystemWillSleep:
		/* The system WILL go to sleep. If you do not call IOAllowPowerChange or
                IOCancelPowerChange to acknowledge this message, sleep will be
               delayed by 30 seconds.

               NOTE: If you call IOCancelPowerChange to deny sleep it returns kIOReturnSuccess,
               however the system WILL still go to sleep.
            */

		// if we are not paused -> pause
		m_pApplication->startPause();
		// we cannot deny forced sleep
		IOAllowPowerChange(root_port, (long)messageArgument);
		break;

	case kIOMessageSystemWillPowerOn:
		m_pApplication->m_bSuspendEvent = true;
		// Delay seems to be necessary for SDL_GetTicks to work properly (?)
		SDL_Delay(1000);
		/* The system WILL wake up*/
		break;
	default:
		break;
	}
}
#endif

void Application::init()
{
	SDL_Log("Starting MacBomber v. 0.5.1");

	//load Config first, since we need to know which screen resolution to use
	m_pConfig = new Config();
	m_pConfig->loadConfig();

	initSDL();
	initGL();
	sizeGLWindow();

	screenWidth = m_pConfig->getScreenWidth();
	screenHeight = m_pConfig->getScreenHeight();

	m_pSoundManager = new SoundManager(m_pMixer);

	m_iState = MENU;
	m_pClock = new Clock();

	m_pCamera = new Camera();
	m_pCamera->setPreset(m_pConfig->getCameraPreset());
	m_pMapManager = new MapManager();

	m_pMeshManager = new MeshManager();
	m_pTextureManager = new TextureManager();
	m_pTextureManager->loadTextures();

	m_pTextDrawer = new TextDrawer();
	m_pScreenFader = new ScreenFader();

	m_pInputManager = new InputManager(this);
	m_pMainMenu = new ApplicationMenu(this);

	m_bSuspendEvent = false;
	setState(MENU);

	//initiate "random" number generator
	srand(time(NULL));
}

void Application::render()
{
	//    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

#ifdef FREECAMERA
	m_pCamera->setViewByMouse();
#endif
	m_pCamera->setView();

	switch (m_iState) {
	case MENU:
		m_pMainMenu->draw();
		break;
	case GAME_PAUSED:
	case GAME:
		m_pGame->draw();
		break;
	case QUIT:
		break;
	}

	SDL_GL_SwapWindow(m_pWindow);
}

void Application::startNewGame()
{
	// set Game state
	m_iState = GAME;

	//start Game - depending on selected gametype
	switch (m_pConfig->getGameType()) {
	case 0:
		m_pGame = new Game_Standard(this);
		break;
	case 1:
		m_pGame = new Game_MapDestruction(this);
		break;
	default:
		m_pGame = new Game_Standard(this);
		break;
	}
}

void Application::run()
{
	Uint64 time1 = SDL_GetTicks();
	Uint64 time0 = time1;
	int numLoops = 0;

	while (m_iState != QUIT) {
		//	calculateFramerate();

		time1 = SDL_GetTicks();
		numLoops = 0;

		/*Reset time values once after wake up from sleep.
		  This is needed because, the system doesn't go to sleep immediatley.
		  SDL could be running for a while, while MacBomber isn't updated anymore. This could
		  cause time1 and time0 values to be too small, upon awakening, because the SDL Ticks
		  was kept updated after MacBomber went to bed.   
		 */
		if (m_bSuspendEvent) {
			time1 = SDL_GetTicks();
			time0 = time1;
			m_bSuspendEvent = false;
		}

		while (((time1 - time0) > TICK_TIME) &&
		       (numLoops < MAX_LOOPS)) {
			m_pInputManager->update();
			switch (m_iState) {
			case MENU:
				m_pMainMenu->update();
				break;
			case GAME:
			case GAME_PAUSED:
				m_pGame->update();
				break;
			default:
				break;
			}
			time0 += TICK_TIME;
			numLoops++;
		}
		render();
	}
}

void Application::pause()
{
	//only pause, when game is running
	switch (m_iState) {
	case GAME:
		startPause();
		break;
	case GAME_PAUSED:
		stopPause();
		break;
	default:
		break;
	}
}

void Application::startPause()
{
	//check needed for suspend event
	if (m_iState == GAME) {
		m_pGame->startPause();
		m_pClock->startPause();
		m_pSoundManager->pauseMusic();
		setState(GAME_PAUSED);
	}
}

void Application::stopPause()
{
	//if this method gets called while we are in Pause -> continue!
	m_pGame->stopPause();
	m_pClock->stopPause();
	m_pSoundManager->resumeMusic();
	m_iState = GAME;
}

void Application::setState(int state)
{
	m_iState = state;

	switch (state) {
	case MENU:
		if (m_pGame != NULL) {
			delete m_pGame;
			m_pGame = NULL;
		}
		m_pSoundManager->playMusic(MENU_MUSIC);
		break;
	case GAME:
		m_pSoundManager->stopMusic();
		startNewGame();
		break;
	case QUIT:
		// store which maps were enabled /disabled
		m_pMapManager->storeSettings();
		// store menu settings
		m_pMainMenu->storeSettings();
		// store camera settings
		m_pConfig->setCameraPreset(m_pCamera->getPreset());
		// save everything to config (file)
		m_pConfig->saveConfig();
		break;
	}
}
