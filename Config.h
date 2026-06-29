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

#ifndef CONFIG_H
#define CONFIG_H

#include <SDL3/SDL.h>

class Config {
private:
	bool m_bFullscreen;
	/*	0 = 800x600
		1 = 1024 x 768
		2 = 1280 x 800
	*/
	int m_iResolution;
	int m_iCameraPreset;

	int m_iStartBombs;
	int m_iStartPower;
	int m_iStartSpeed;
	bool m_bStartKick;

	int m_iExtraBombs;
	int m_iExtraPower;
	int m_iExtraSpeed;

	int m_iGameType;
	int m_iRoundTime;
	int m_iPointsForVictory;
	int m_iPlayerCount;

	bool m_bKick;
	bool m_bJoint;
	bool m_bCocaine;
	bool m_bCondom;
	bool m_bViagra;
	bool m_bBomb;
	bool m_bPower;
	bool m_bSpeed;

	bool m_bRandomMapOrder;

	bool m_bPlaySoundFX;
	bool m_bPlayMusic;
	int m_iSoundFXVolume;
	int m_iMusicVolume;

	// an bool array. It tells us which maps are enabled or disabled
	bool m_bMapStatus[150]; // 150 elemennts should be enough
	// how many maps are there actually ?
	int m_iMapCount;

	// This struct contains Player Setups
	struct stPlayer {
		int iKeySet;
		int iSkin;
		char *cName;
		bool bEnabled;
	};
	// There are four active players at most
	stPlayer m_stPlayers[4];

	//struct which contains screen resolution
	struct stResolution {
		// Resolution
		int width;
		int height;
		//supported by system ?
		bool bSupported;
	};
	stResolution m_stResolution[3];

	// the amount by which the player Velocity should be incremented when m_iSpeed++
	float m_fVelocityStepping;

public:
	Config();

	static SDL_Keycode m_iPlayerKeys[4][5];

	void setFullscreen(int value);
	void setResolution(int value)
	{
		m_iResolution = value;
	};
	void setResolutionSupport(int res, bool bSupport);
	void setCameraPreset(int value)
	{
		m_iCameraPreset = value;
	};

	void setStartBombs(int value)
	{
		m_iStartBombs = value;
	};
	void setStartPower(int value)
	{
		m_iStartPower = value;
	};
	void setStartSpeed(int value)
	{
		m_iStartSpeed = value;
	};
	void setStartKick(int value);

	void setExtraBombs(int value)
	{
		m_iExtraBombs = value;
	};
	void setExtraPower(int value)
	{
		m_iExtraPower = value;
	};
	void setExtraSpeed(int value)
	{
		m_iExtraSpeed = value;
	};

	void setGameType(int value)
	{
		m_iGameType = value;
	};
	void setRoundTime(int value)
	{
		m_iRoundTime = value;
	};
	void setPointsForVictory(int value)
	{
		m_iPointsForVictory = value;
	};
	void setRandomMapOrder(int); // 0 = false, 1 = true
	void setPlayerCount(int value)
	{
		m_iPlayerCount = value;
	}
	void setSoundFXVolume(int value)
	{
		m_iSoundFXVolume = value;
	}; // 0-8
	void setMusicVolume(int value)
	{
		m_iMusicVolume = value;
	};

	void setKick(int); // 0 = false, 1 = true
	void setJoint(int); // 0 = false, 1 = true
	void setCocaine(int); // 0 = false, 1 = true
	void setCondom(int); // 0 = false, 1 = true
	void setViagra(int); // 0 = false, 1 = true
	void setBomb(int); // 0 = false, 1 = true
	void setPower(int); // 0 = false, 1 = true
	void setSpeed(int); // 0 = false, 1 = true

	void setSoundFX(int); // 0 = false, 1 = true
	void setMusic(int);
	//-----------------------------

	bool getFullscreen()
	{
		return m_bFullscreen;
	};
	//return current resolution width and height
	int getScreenWidth();
	int getScreenHeight();
	int getResolutionWidth(int index);
	int getResolutionHeight(int index);
	bool getResolutionSupport(int index)
	{
		return m_stResolution[index].bSupported;
	};
	//return the index of the current resolution
	int getResolution()
	{
		return m_iResolution;
	};
	int getCameraPreset()
	{
		return m_iCameraPreset;
	};

	int getStartBombs()
	{
		return m_iStartBombs;
	};
	int getStartPower()
	{
		return m_iStartPower;
	};
	int getStartSpeed()
	{
		return m_iStartSpeed;
	};
	bool getStartKick()
	{
		return m_bStartKick;
	};
	int getExtraBombs()
	{
		return m_iExtraBombs;
	};
	int getExtraPower()
	{
		return m_iExtraPower;
	};
	int getExtraSpeed()
	{
		return m_iExtraSpeed;
	};

	int getGameType()
	{
		return m_iGameType;
	};
	int getRoundTime()
	{
		return m_iRoundTime;
	};
	int getPointsForVictory()
	{
		return m_iPointsForVictory;
	};
	int getPlayerCount()
	{
		return m_iPlayerCount;
	};

	int getSoundFXVolume()
	{
		return m_iSoundFXVolume;
	};
	int getMusicVolume()
	{
		return m_iMusicVolume;
	};

	bool getKick()
	{
		return m_bKick;
	};
	bool getJoint()
	{
		return m_bJoint;
	};
	bool getCocaine()
	{
		return m_bCocaine;
	};
	bool getCondom()
	{
		return m_bCondom;
	};
	bool getViagra()
	{
		return m_bViagra;
	};
	bool getBomb()
	{
		return m_bBomb;
	};
	bool getPower()
	{
		return m_bPower;
	};
	bool getSpeed()
	{
		return m_bSpeed;
	};

	bool getRandomMapOrder()
	{
		return m_bRandomMapOrder;
	};

	bool getSoundFX()
	{
		return m_bPlaySoundFX;
	};
	bool getMusic()
	{
		return m_bPlayMusic;
	};

	int getPlayerKeySet(int playerNr);
	int getKey(int keyset, int keyID);
	int getPlayerSkin(int playerNr);
	bool isPlayerEnabled(int playerNr);
	void setPlayerKeySet(int playerNr, int keyset);
	void setPlayerSkin(int playerNr, int skin);
	void setPlayerEnabled(int playerNr, bool enabled);

	float getVelocityStepping()
	{
		return m_fVelocityStepping;
	};

	// set the map with index nr to enabled/diabled
	void setMapStatus(int nr, bool bValue);
	bool getMapStatus(int nr)
	{
		return m_bMapStatus[nr];
	};
	void setMapCount(int nr)
	{
		m_iMapCount = nr;
	};

	//saves / loads config from disk
	void saveConfig();
	void loadConfig();

	//prints config to console
	void showConfig() {};
};

#endif
