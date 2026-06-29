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
#include <iostream>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>
#include <SDL3_mixer/SDL_mixer.h>

#include "intToString.h"
#include "checkScreenResolution.h"
#include "../Config.h"
#include "../Application.h"

using namespace std;

// Initialize SDL
void initSDL()
{
	cout << "SDL: Init VIDEO|AUDIO" << endl;
	// Initialize video system and joystick input
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO)) {
		cout << "SDL: Couldn't initialize. Error:" << SDL_GetError()
		     << endl;
		SDL_Quit();
	}

	// AUDIO 48000
	// Note: Dennis sampled the song at 48000 sample rate... maybe less would be better?
	if (!MIX_Init()) {
		cout << "SDL: Failed initializing mixer. Error:"
		     << SDL_GetError() << endl;
		SDL_Quit();
	}

	SDL_AudioSpec audioSpec = { SDL_AUDIO_S16, 2, 48000 };
	Application::m_pMixer = MIX_CreateMixerDevice(
		SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec);
	if (Application::m_pMixer == NULL) {
		cout << "SDL: Failed opening Audio Device. Error:"
		     << SDL_GetError() << endl;
		SDL_Quit();
	}

	//check for supported resolutions
	for (int i = 0; i < 3; i++)
		Application::m_pConfig->setResolutionSupport(
			i, isResolutionSupported(i));

	/*	check if the *requested* resolution is supported
		(if not default to 800x600 which (hopefully) should work everywhere)
		This is necessary to ensure that someone who for e.g moved the MacBomber
		binary from one System to another won't be able to start with an
		resolution setting, which isn't supported by the new system
	*/

	if (!Application::m_pConfig->getResolutionSupport(
		    Application::m_pConfig->getResolution()))
		Application::m_pConfig->setResolution(0);

	int width = Application::m_pConfig->getScreenWidth();
	int height = Application::m_pConfig->getScreenHeight();

	cout << "SDL: Setting Resolution " << width << " x " << height;
	if (Application::m_pConfig->getFullscreen())
		cout << " (fullscreen)" << endl;
	else
		cout << " (window)" << endl;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	if (Application::m_pConfig->getFullscreen())
		windowFlags |= SDL_WINDOW_FULLSCREEN;

	Application::m_pWindow = SDL_CreateWindow("MacBomber v.0.5.1", width,
						  height, windowFlags);
	if (Application::m_pWindow == NULL) {
		cout << "SDL: Error creating window: " << SDL_GetError()
		     << endl;
		SDL_Quit();
	}

	Application::m_glContext = SDL_GL_CreateContext(Application::m_pWindow);
	if (Application::m_glContext == NULL) {
		cout << "SDL: Error creating GL context: " << SDL_GetError()
		     << endl;
		SDL_Quit();
	}

	// set initial mouse position
	SDL_WarpMouseInWindow(Application::m_pWindow, width / 2.0f,
			      height / 2.0f);

	SDL_HideCursor();
}

// Initialize OpenGL
int initGL()
{
	// activate vsyncing
	SDL_GL_SetSwapInterval(1);

	// Enable smooth shading
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);

	// The color used to clear the screen
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

// Reset some OpenGL parameters when the window size has changed
int sizeGLWindow()
{
	int screenWidth = Application::m_pConfig->getScreenWidth();
	int screenHeight = Application::m_pConfig->getScreenHeight();

	// Since we divide width by height, we must ensure height is not "0"
	if (screenHeight == 0)
		screenHeight = 1;

	// Our viewport is the entire screen
	glViewport(0, 0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION); // Select the projection matrix
	glLoadIdentity(); // Reset the projection matrix

	//		Field of view	Aspect ratio	Camera clipping distance
	//						     near   far
	gluPerspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1,
		       150.0f);

	glMatrixMode(GL_MODELVIEW); // Select the modelview matrix
	glLoadIdentity(); // Reset the modelview matrix

	return 1;
}

void dumpScreen()
{
	int screenWidth = Application::m_pConfig->getScreenWidth();
	int screenHeight = Application::m_pConfig->getScreenHeight();

	static int count = 0;
	string strPath("/Users/quarus/");
	string strFileBaseName("macbomber");

	SDL_Surface *screen = SDL_CreateSurface(screenWidth, screenHeight,
#if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
						SDL_PIXELFORMAT_ABGR8888
#else
						SDL_PIXELFORMAT_RGBA8888
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
		SDL_memcpy(pixels + (screenHeight - i - 1) * screenWidth * 4,
			   pixelsbuf + i * screenWidth * 4, screenWidth * 4);

	screen->pixels = pixels;
	string fullpath = strPath + strFileBaseName +
			  convertValueToString(count) + ".bmp";
	printf("Dumping Screenshot: %s\n", fullpath.c_str());
	SDL_SaveBMP(screen, fullpath.c_str());

	SDL_DestroySurface(screen);
	screen = 0;

	//	delete pixels; <- freed in SDL_DestroySurface(screen);
	delete[] pixelsbuf;
	count++;
}
