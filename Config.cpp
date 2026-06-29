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

#include <iostream>
#include <fstream>
#include <string>

#include "Config.h"
#include <SDL.h>
#include "Application.h"
/*
int Config::m_iPlayerKeys[4][5]
=	{SDLK_k,SDLK_l,SDLK_i,SDLK_j,SDLK_u,
	SDLK_DOWN,SDLK_RIGHT,SDLK_UP,SDLK_LEFT,SDLK_RETURN,
	SDLK_s,SDLK_d,SDLK_w,SDLK_a,SDLK_q,
	SDLK_b,SDLK_n,SDLK_g,SDLK_v,SDLK_f
	}; // UP/DOWN geflippt!

*/
//	0		1			2		3		4		5
//UP (z+) RIGHT (x+) DOWN (z-) LEFT (x-) NONE BOMB
int Config::m_iPlayerKeys[4][5] = {
	SDLK_i,	   SDLK_l,    SDLK_k,	   SDLK_j, SDLK_u, SDLK_UP, SDLK_RIGHT,
	SDLK_DOWN, SDLK_LEFT, SDLK_RETURN, SDLK_w, SDLK_d, SDLK_s,  SDLK_a,
	SDLK_q,	   SDLK_g,    SDLK_n,	   SDLK_b, SDLK_v, SDLK_f
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
	string fileName = Application::expandResourcePath("/Config.cfg");
	//create an Output File stream
	ofstream configfile(fileName.c_str());
	if (!configfile) {
		cout << "Config: Couldn't save Config.cfg" << endl;
		return;
	}

	//	printf("%s\n",fileName.c_str());
	configfile << "1" << endl; //Version

	// Game Options
	configfile << m_iStartBombs << endl;
	configfile << m_iStartPower << endl;
	configfile << m_iStartSpeed << endl;
	configfile << m_bStartKick << endl;

	configfile << m_iExtraBombs << endl;
	configfile << m_iExtraPower << endl;
	configfile << m_iExtraSpeed << endl;

	configfile << m_iGameType << endl;
	configfile << m_iRoundTime << endl;
	configfile << m_iPointsForVictory << endl;
	configfile << m_iPlayerCount << endl;

	configfile << m_bKick << endl;
	configfile << m_bJoint << endl;
	configfile << m_bCocaine << endl;
	configfile << m_bCondom << endl;
	configfile << m_bViagra << endl;
	configfile << m_bBomb << endl;
	configfile << m_bPower << endl;
	configfile << m_bSpeed << endl;
	configfile << m_bRandomMapOrder << endl;

	//Audio Options
	configfile << m_bPlaySoundFX << endl;
	configfile << m_bPlayMusic << endl;
	configfile << m_iSoundFXVolume << endl;
	configfile << m_iMusicVolume << endl;

	//Video Options
	configfile << m_bFullscreen << endl;
	configfile << m_iResolution << endl;

	//Camera Option
	configfile << m_iCameraPreset << endl;

	//Player Setup
	for (int i = 0; i < 4; i++) {
		configfile << m_stPlayers[i].iKeySet << endl;
		configfile << m_stPlayers[i].iSkin << endl;
		configfile << m_stPlayers[i].bEnabled << endl;
	}

	//Map Settings
	configfile << m_iMapCount << endl;
	for (int i = 0; i < m_iMapCount; i++)
		configfile << m_bMapStatus[i] << endl;

	configfile.close();
}

void Config::loadConfig()
{
	string fileName = Application::expandResourcePath("/Config.cfg");
	//create an Input File stream
	ifstream configfile(fileName.c_str());
	if (!configfile) {
		cout << "Config: Couldn't open Config.cfg. Using defaults instead!"
		     << endl;
		return;
	}

	int version;
	configfile >> version; //Version

	if (version != 1) {
		cout << "Config: Wrong version. Using defaults instead!"
		     << endl;
		return;
	}
	// Game Options

	configfile >> m_iStartBombs;
	configfile >> m_iStartPower;
	configfile >> m_iStartSpeed;
	configfile >> m_bStartKick;

	configfile >> m_iExtraBombs;
	configfile >> m_iExtraPower;
	configfile >> m_iExtraSpeed;

	configfile >> m_iGameType;
	configfile >> m_iRoundTime;
	configfile >> m_iPointsForVictory;
	configfile >> m_iPlayerCount;

	configfile >> m_bKick;
	configfile >> m_bJoint;
	configfile >> m_bCocaine;
	configfile >> m_bCondom;
	configfile >> m_bViagra;
	configfile >> m_bBomb;
	configfile >> m_bPower;
	configfile >> m_bSpeed;
	configfile >> m_bRandomMapOrder;

	//Audio Options
	configfile >> m_bPlaySoundFX;
	configfile >> m_bPlayMusic;
	configfile >> m_iSoundFXVolume;
	configfile >> m_iMusicVolume;

	//Video Options
	configfile >> m_bFullscreen;
	configfile >> m_iResolution;

	//Camera Option
	configfile >> m_iCameraPreset;

	//Player Setup
	for (int i = 0; i < 4; i++) {
		configfile >> m_stPlayers[i].iKeySet;
		configfile >> m_stPlayers[i].iSkin;
		configfile >> m_stPlayers[i].bEnabled;
	}

	//Map Settings
	configfile >> m_iMapCount;
	for (int i = 0; i < m_iMapCount; i++)
		configfile >> m_bMapStatus[i];

	configfile.close();
}
