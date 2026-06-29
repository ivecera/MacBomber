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

#include "Init.h"
#include <iostream.h>
#include <GLUT/glut.h>
#include <Opengl/Opengl.h>
#include <string>
#include "SDL_mixer/SDL_mixer.h"

#include "intToString.h"
#include "checkScreenResolution.h"
#include "Config.h"
#include "Application.h"
#include "Workaround.h"

using namespace std;

SDL_Surface *screen;

// Initialisiert SDL
void initSDL()
{
	// Enthaelt Informationen ¸ber das Video Systems
	const SDL_VideoInfo *videoInfo;
	int videoFlags = 0;
	int audio_buffers = 1024;

	cout << "SDL: Init VIDEO|AUDIO" << endl;
	// Initialisiere Video System sowie Joystick Input
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER |
		     SDL_INIT_AUDIO) < 0) {
		cout << "SDL: Couldn't initialize. Error:" << SDL_GetError()
		     << endl;
		SDL_Quit();
	}

	// AUDIO 44100
	// Hinweis: Dennis hat den song mit 48000 abtastrarte gesampelt...vielleicht w�re weniger besser?
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, audio_buffers) < 0) {
		cout << "SDL: Failed opening Audio Device. Error:"
		     << SDL_GetError() << endl;
		SDL_Quit();
	}

	// VIDEO
	videoInfo = SDL_GetVideoInfo();

	if (videoInfo == NULL) {
		cout << "SDL: Couldn't read Videoinfo. Error:" << SDL_GetError()
		     << endl;
		SDL_Quit();
	}

	/*
	cout << "SDL: VideoInfo: " << endl;
	cout << "     Video Memory:	" << videoInfo->video_mem << endl;
	cout << "     Video HW_Surface:	" << videoInfo->hw_available << endl;
	cout << "     Video blit_hw   :	" << videoInfo->blit_hw << endl;
	*/

	// Wir erzeugen uns ein Integer mit den entsprechenden Flags
	videoFlags = SDL_OPENGL; // Aktiviere OpenGL in SDL
	videoFlags |=
		SDL_GL_DOUBLEBUFFER; // Aktiviere Double Buffering in SDL mit OpenGL
	videoFlags |= SDL_RESIZABLE; // Fenstergrˆﬂe soll variabl sein
	videoFlags |= SDL_HWPALETTE; // Speichere die Palette in Hardware

	// Kˆnnen Hardware Surfaces benutzt werden ?
	if (videoInfo->hw_available) {
		videoFlags |= SDL_HWSURFACE;
		cout << "SDL: Using Hardware Surfaces. " << endl;

	} else {
		videoFlags |= SDL_SWSURFACE;
		cout << "SDL: Using Software Surfaces. " << endl;
	}

	// Kann Hardware Beschleunigung benutzt werden ?
	if (videoInfo->blit_hw) {
		videoFlags |= SDL_HWACCEL;
		cout << "SDL: Using Hardware Acceleration " << endl;
	}

	if (Application::m_pConfig->getFullscreen())
		videoFlags |= SDL_FULLSCREEN;

	//check for supported resolutions
	for (int i = 0; i < 3; i++) {
		if (isResolutionSupported(i))
			Application::m_pConfig->setResolutionSupport(i, true);
		else
			Application::m_pConfig->setResolutionSupport(i, false);
	}

	//doesn't work yet. SDL version is too old
	//SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, TRUE);

	/*	check if the *requested* resolution is supported
		(if not default to 800x600 which (hopefully) should work everywhere)
		This is necessary to ensure that someone who for e.g moved the MacBomber
		binary from one System to another won't be able to start with an 
		resolution setting, which isn't supported by the new system
	*/

	if (!Application::m_pConfig->getResolutionSupport(
		    Application::m_pConfig->getResolution()))
		Application::m_pConfig->setResolution(0);

	cout << "SDL: Setting Resolution "
	     << Application::m_pConfig->getScreenWidth() << " x "
	     << Application::m_pConfig->getScreenHeight();
	if (Application::m_pConfig->getFullscreen())
		cout << " (fullscreen)" << endl;
	else
		cout << " (window)" << endl;

	screen = SDL_SetVideoMode(Application::m_pConfig->getScreenWidth(),
				  Application::m_pConfig->getScreenHeight(), 32,
				  videoFlags);
	if (screen == NULL) {
		cout << "SDL: Error setting video mode. (Propably not supported by Hardware)"
		     << endl;
		SDL_Quit();
	}

	SDL_WM_SetCaption("MacBomber v.0.5.1", NULL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// set initial mouse position
	SDL_WarpMouse(Application::m_pConfig->getScreenWidth() / 2,
		      Application::m_pConfig->getScreenHeight() / 2);

	SDL_ShowCursor(SDL_DISABLE);
}

// Initialisiert OpenGL
int initGL()
{
	//activate vsyncing
	long VBL = 1;
	CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &VBL);

	// aktiviere Smooth Shadows
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);

	// Die Farbe mit der der Bildschirm gelˆscht werden soll
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor ( 1.0f, 0.58f, 0.0f, 0.0f );
	/* Depth buffer setup */
	glClearDepth(1.0f);
	/* Enables Depth Testing */
	glEnable(GL_DEPTH_TEST);
	/* The Type Of Depth Test To Do */
	glDepthFunc(GL_LEQUAL);

	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_NORMALIZE);

	// --------------------------- Lightning -----------------------
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	float light1_ambient[4] = { 0.5, 0.5, 0.5, 1.0 };
	float light1_diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };
	float light1_specular[4] = { 1, 1, 1, 1.0 };

	// 0 - directional light source
	// 1 - positional light source
	float light1_position[4] = { 9.5, 17, 13, 1 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT1);

	//	glEnable(GL_FOG);
	GLfloat fogColor[4] = { 0.0, 0.0, 0.0, 1.0 };
	glFogf(GL_FOG_START, 18);
	glFogf(GL_FOG_END, 25.0);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.5);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	return 1;
}

// Setzt einige OpenGL Parameter neu, wenn die Fenstergrˆsse ver‰ndert wurde
int sizeGLWindow()
{
	int screenWidth = Application::m_pConfig->getScreenWidth();
	int screenHeight = Application::m_pConfig->getScreenHeight();

	// Da wir width durch Height dividieren werden, m¸ssen wir ausschlieﬂen, dass Height "0" ist
	if (screenWidth == 0)
		screenHeight = 1;

	// Unser Viewport ist der gesamte Bildschirm
	glViewport(0, 0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION); // w‰hle die Projektionsmatrix
	glLoadIdentity(); // Resete die Projektionsmatrix

	//		Blickwinkel	Relation	Entfernung Kamera bis geclippt wird
	//						     nah   fern
	gluPerspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1,
		       150.0f);

	glMatrixMode(GL_MODELVIEW); // w‰hle die Modelview Matrix
	glLoadIdentity(); // Resete die Modelview Matrix

	return 1;
}

void dumpScreen()
{
	int screenWidth = Application::m_pConfig->getScreenWidth();
	int screenHeight = Application::m_pConfig->getScreenHeight();

	static int count = 0;
	string strPath("/Users/quarus/");
	string strFileBaseName("macbomber");

	SDL_Surface *screen = SDL_CreateRGBSurface(
		SDL_SWSURFACE, screenWidth, screenHeight, 32,
#if (SDL_BYTEORDER == SDL_LIL_ENDIAN) /* OpenGL RGBA masks */
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#else
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#endif
	);

	//create an array with width*Height*4(RGBA) Bytes
	unsigned char *pixelsbuf =
		new unsigned char[screenWidth * screenHeight * 4];
	unsigned char *pixels =
		new unsigned char[screenWidth * screenHeight * 4];

	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, screenWidth, screenHeight, GL_RGBA, GL_UNSIGNED_BYTE,
		     pixelsbuf);

	// flip image vertically...
	for (int i = 0; i < screenHeight; ++i)
		memcpy(pixels + (screenHeight - i - 1) * screenWidth * 4,
		       pixelsbuf + i * screenWidth * 4, screenWidth * 4);

	screen->pixels = pixels;
	string fullpath = strPath + strFileBaseName +
			  convertValueToString(count) + ".bmp";
	printf("Dumping Screenshot: %s\n", fullpath.c_str());
	SDL_SaveBMP(screen, fullpath.c_str());

	SDL_FreeSurface(screen);
	screen = 0;

	//	delete pixels; <- freed in SDL_FreeSurface(screen);
	delete pixelsbuf;
	count++;
}
