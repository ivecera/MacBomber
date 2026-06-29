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

#include <string>

#include "Config.h"
#include <SDL3/SDL.h>
#include "Application.h"
/*
int Config::m_iPlayerKeys[4][5]
=	{SDLK_K,SDLK_L,SDLK_I,SDLK_J,SDLK_U,
	SDLK_DOWN,SDLK_RIGHT,SDLK_UP,SDLK_LEFT,SDLK_RETURN,
	SDLK_S,SDLK_D,SDLK_W,SDLK_A,SDLK_Q,
	SDLK_B,SDLK_N,SDLK_G,SDLK_V,SDLK_F
	}; // UP/DOWN geflippt!

*/
//	0		1			2		3		4		5
//UP (z+) RIGHT (x+) DOWN (z-) LEFT (x-) NONE BOMB
int Config::m_iPlayerKeys[4][5] = {
	SDLK_I,	   SDLK_L,    SDLK_K,	   SDLK_J, SDLK_U, SDLK_UP, SDLK_RIGHT,
	SDLK_DOWN, SDLK_LEFT, SDLK_RETURN, SDLK_W, SDLK_D, SDLK_S,  SDLK_A,
	SDLK_Q,	   SDLK_G,    SDLK_N,	   SDLK_B, SDLK_V, SDLK_F
};

Config::Config()
{
	m_iStartBombs = 1;
	m_iStartPower = 1;
	m_iStartSpeed = 1;
	m_bStartKick = false;

	m_iExtraBombs = 9;
	m_iExtraPower = 12;
	m_iExtraSpeed = 5;

	m_iGameType = 0;
	m_iRoundTime = 120;
	m_iPointsForVictory = 3;
	m_iPlayerCount = 2;

	m_bKick = true;
	m_bJoint = true;
	m_bCocaine = true;
	m_bCondom = true;
	m_bViagra = true;
	m_bBomb = true;
	m_bPower = true;
	m_bSpeed = true;
	m_bRandomMapOrder = false;

	m_bPlaySoundFX = true;
	m_bPlayMusic = true;
	m_iSoundFXVolume = 2;
	m_iMusicVolume = 1;

	m_fVelocityStepping = 0.25;

	//init players
	for (int i = 0; i < 4; i++) {
		m_stPlayers[i].iKeySet = i;
		m_stPlayers[i].iSkin = i;
		m_stPlayers[i].bEnabled = true;
	}

	//init resolutions
	m_stResolution[0].width = 800;
	m_stResolution[0].height = 600;
	m_stResolution[0].bSupported = true;

	m_stResolution[1].width = 1024;
	m_stResolution[1].height = 768;
	m_stResolution[1].bSupported = true;

	m_stResolution[2].width = 1280;
	m_stResolution[2].height = 800;
	m_stResolution[2].bSupported = false;

	m_bFullscreen = false;
	m_iResolution = 0;
	m_iCameraPreset = 0;

	for (int i = 0; i < 150; i++)
		m_bMapStatus[i] = true;
	m_iMapCount = 0;
}

void Config::setFullscreen(int value)
{
	(value > 0) ? m_bFullscreen = true : m_bFullscreen = false;
}

void Config::setResolutionSupport(int res, bool bSupport)
{
	if ((res >= 0) && (res < 3)) {
		m_stResolution[res].bSupported = bSupport;
	}
}

void Config::setRandomMapOrder(int value)
{
	(value > 0) ? m_bRandomMapOrder = true : m_bRandomMapOrder = false;
}

void Config::setStartKick(int value)
{
	(value > 0) ? m_bStartKick = true : m_bStartKick = false;
}

void Config::setKick(int value)
{
	(value > 0) ? m_bKick = true : m_bKick = false;
}

void Config::setJoint(int value)
{
	(value > 0) ? m_bJoint = true : m_bJoint = false;
}

void Config::setCocaine(int value)
{
	(value > 0) ? m_bCocaine = true : m_bCocaine = false;
}

void Config::setCondom(int value)
{
	(value > 0) ? m_bCondom = true : m_bCondom = false;
}

void Config::setViagra(int value)
{
	(value > 0) ? m_bViagra = true : m_bViagra = false;
}

void Config::setBomb(int value)
{
	(value > 0) ? m_bBomb = true : m_bBomb = false;
}

void Config::setPower(int value)
{
	(value > 0) ? m_bPower = true : m_bPower = false;
}

void Config::setSpeed(int value)
{
	(value > 0) ? m_bSpeed = true : m_bSpeed = false;
}

void Config::setSoundFX(int value)
{
	(value > 0) ? m_bPlaySoundFX = true : m_bPlaySoundFX = false;
}

void Config::setMusic(int value)
{
	(value > 0) ? m_bPlayMusic = true : m_bPlayMusic = false;
}

int Config::getScreenWidth()
{
	return m_stResolution[m_iResolution].width;
}

int Config::getScreenHeight()
{
	return m_stResolution[m_iResolution].height;
}

int Config::getResolutionWidth(int index)
{
	return m_stResolution[index].width;
}

int Config::getResolutionHeight(int index)
{
	return m_stResolution[index].height;
}

int Config::getPlayerKeySet(int playerNr)
{
	return m_stPlayers[playerNr].iKeySet;
}

int Config::getKey(int keyset, int keyID)
{
	return m_iPlayerKeys[keyset][keyID];
}

int Config::getPlayerSkin(int playerNr)
{
	return m_stPlayers[playerNr].iSkin;
}

bool Config::isPlayerEnabled(int playerNr)
{
	return m_stPlayers[playerNr].bEnabled;
}

void Config::setPlayerKeySet(int playerNr, int keyset)
{
	//	printf(" keyset.: %i\n",keyset);
	m_stPlayers[playerNr].iKeySet = keyset;
}

void Config::setPlayerSkin(int playerNr, int skin)
{
	m_stPlayers[playerNr].iSkin = skin;
}

void Config::setPlayerEnabled(int playerNr, bool enabled)
{
	m_stPlayers[playerNr].bEnabled = enabled;
}

void Config::setMapStatus(int nr, bool bValue)
{
	//	if ( ( nr >= 0) && ( nr < m_iMapCount) )
	m_bMapStatus[nr] = bValue;
}

void Config::saveConfig()
{
	string fileName = Application::expandPrefPath("Config.cfg");
	SDL_IOStream *io = SDL_IOFromFile(fileName.c_str(), "w");
	if (!io) {
		SDL_Log("Config: Couldn't save Config.cfg");
		return;
	}

	SDL_IOprintf(io, "%d\n", 1); //Version

	// Game Options
	SDL_IOprintf(io, "%d\n", m_iStartBombs);
	SDL_IOprintf(io, "%d\n", m_iStartPower);
	SDL_IOprintf(io, "%d\n", m_iStartSpeed);
	SDL_IOprintf(io, "%d\n", m_bStartKick);

	SDL_IOprintf(io, "%d\n", m_iExtraBombs);
	SDL_IOprintf(io, "%d\n", m_iExtraPower);
	SDL_IOprintf(io, "%d\n", m_iExtraSpeed);

	SDL_IOprintf(io, "%d\n", m_iGameType);
	SDL_IOprintf(io, "%d\n", m_iRoundTime);
	SDL_IOprintf(io, "%d\n", m_iPointsForVictory);
	SDL_IOprintf(io, "%d\n", m_iPlayerCount);

	SDL_IOprintf(io, "%d\n", m_bKick);
	SDL_IOprintf(io, "%d\n", m_bJoint);
	SDL_IOprintf(io, "%d\n", m_bCocaine);
	SDL_IOprintf(io, "%d\n", m_bCondom);
	SDL_IOprintf(io, "%d\n", m_bViagra);
	SDL_IOprintf(io, "%d\n", m_bBomb);
	SDL_IOprintf(io, "%d\n", m_bPower);
	SDL_IOprintf(io, "%d\n", m_bSpeed);
	SDL_IOprintf(io, "%d\n", m_bRandomMapOrder);

	//Audio Options
	SDL_IOprintf(io, "%d\n", m_bPlaySoundFX);
	SDL_IOprintf(io, "%d\n", m_bPlayMusic);
	SDL_IOprintf(io, "%d\n", m_iSoundFXVolume);
	SDL_IOprintf(io, "%d\n", m_iMusicVolume);

	//Video Options
	SDL_IOprintf(io, "%d\n", m_bFullscreen);
	SDL_IOprintf(io, "%d\n", m_iResolution);

	//Camera Option
	SDL_IOprintf(io, "%d\n", m_iCameraPreset);

	//Player Setup
	for (int i = 0; i < 4; i++) {
		SDL_IOprintf(io, "%d\n", m_stPlayers[i].iKeySet);
		SDL_IOprintf(io, "%d\n", m_stPlayers[i].iSkin);
		SDL_IOprintf(io, "%d\n", m_stPlayers[i].bEnabled);
	}

	//Map Settings
	SDL_IOprintf(io, "%d\n", m_iMapCount);
	for (int i = 0; i < m_iMapCount; i++)
		SDL_IOprintf(io, "%d\n", m_bMapStatus[i]);

	SDL_CloseIO(io);
}

static int readInt(char **pos)
{
	int val = 0;
	SDL_sscanf(*pos, "%d", &val);
	*pos = SDL_strchr(*pos, '\n');
	if (*pos)
		(*pos)++;
	return val;
}

void Config::loadConfig()
{
	string fileName = Application::expandPrefPath("Config.cfg");
	SDL_IOStream *io = SDL_IOFromFile(fileName.c_str(), "r");
	if (!io) {
		SDL_Log("Config: Couldn't open Config.cfg. Using defaults instead!");
		return;
	}

	Sint64 size = SDL_GetIOSize(io);
	char *data = (char *)SDL_malloc(size + 1);
	SDL_ReadIO(io, data, size);
	data[size] = '\0';
	SDL_CloseIO(io);

	char *pos = data;

	int version = readInt(&pos);
	if (version != 1) {
		SDL_Log("Config: Wrong version. Using defaults instead!");
		SDL_free(data);
		return;
	}

	// Game Options
	m_iStartBombs = readInt(&pos);
	m_iStartPower = readInt(&pos);
	m_iStartSpeed = readInt(&pos);
	m_bStartKick = readInt(&pos);

	m_iExtraBombs = readInt(&pos);
	m_iExtraPower = readInt(&pos);
	m_iExtraSpeed = readInt(&pos);

	m_iGameType = readInt(&pos);
	m_iRoundTime = readInt(&pos);
	m_iPointsForVictory = readInt(&pos);
	m_iPlayerCount = readInt(&pos);

	m_bKick = readInt(&pos);
	m_bJoint = readInt(&pos);
	m_bCocaine = readInt(&pos);
	m_bCondom = readInt(&pos);
	m_bViagra = readInt(&pos);
	m_bBomb = readInt(&pos);
	m_bPower = readInt(&pos);
	m_bSpeed = readInt(&pos);
	m_bRandomMapOrder = readInt(&pos);

	//Audio Options
	m_bPlaySoundFX = readInt(&pos);
	m_bPlayMusic = readInt(&pos);
	m_iSoundFXVolume = readInt(&pos);
	m_iMusicVolume = readInt(&pos);

	//Video Options
	m_bFullscreen = readInt(&pos);
	m_iResolution = readInt(&pos);

	//Camera Option
	m_iCameraPreset = readInt(&pos);

	//Player Setup
	for (int i = 0; i < 4; i++) {
		m_stPlayers[i].iKeySet = readInt(&pos);
		m_stPlayers[i].iSkin = readInt(&pos);
		m_stPlayers[i].bEnabled = readInt(&pos);
	}

	//Map Settings
	m_iMapCount = readInt(&pos);
	for (int i = 0; i < m_iMapCount; i++)
		m_bMapStatus[i] = readInt(&pos);

	SDL_free(data);
}
