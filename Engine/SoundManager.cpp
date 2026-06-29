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

#include "SoundManager.h"
#include "../Defines.h"
#include "../Config.h"
#include "../Application.h"

#include <iostream>

SoundManager::SoundManager()
{
	m_Samples[EXPlOSION_SOUND] = Mix_LoadWAV(
		Application::expandResourcePath("/Sounds/explode.wav").c_str());
	m_Samples[PUTBOMB_SOUND] = Mix_LoadWAV(
		Application::expandResourcePath("/Sounds/putbomb.wav").c_str());
	m_Samples[CRUNCH_SOUND] = Mix_LoadWAV(
		Application::expandResourcePath("/Sounds/crunch.wav").c_str());

	m_Music[MENU_MUSIC] = Mix_LoadMUS(
		Application::expandResourcePath("/Sounds/macbomber_theme.mp3")
			.c_str());
	m_Music[SCORESCREEN_MUSIC] = Mix_LoadMUS(
		Application::expandResourcePath("/Sounds/macbomber_fanfare.mp3")
			.c_str());
	m_Music[GAME_MUSIC] = Mix_LoadMUS(
		Application::expandResourcePath("/Sounds/macbomber_game.mp3")
			.c_str());

	m_bMusicPlaying = false;
	m_bLoopMusic = false;
	;
	m_bMusicWaiting = false;
	Mix_HookMusicFinished(SoundManager::musicDone);
}

SoundManager::~SoundManager()
{
	Mix_FreeChunk(m_Samples[EXPlOSION_SOUND]);
	Mix_FreeChunk(m_Samples[PUTBOMB_SOUND]);

	Mix_HaltMusic();
	Mix_FreeMusic(m_Music[MENU_MUSIC]);
	Mix_FreeMusic(m_Music[SCORESCREEN_MUSIC]);
	Mix_FreeMusic(m_Music[GAME_MUSIC]);
}

void SoundManager::musicDone()
{
	Application::m_pSoundManager->handelMusicDone();
}

void SoundManager::setVolumeSoundFX(int vol)
{
	// Maximum: 125; 125/ 5 = 25
	Mix_Volume(-1, 25 * vol);
}

void SoundManager::setVolumeMusic(int vol)
{
	//Maximum: 128; 128 / 5 ~= 25
	Mix_VolumeMusic(25 * vol);
}

void SoundManager::playSoundFX(int nr)
{
	//Only Play if Sound is enabled
	if (Application::m_pConfig->getSoundFX())
		Mix_PlayChannel(-1, m_Samples[nr], 0);
}

void SoundManager::handelMusicDone()
{
	if (m_bMusicWaiting) {
		Mix_FadeInMusic(m_Music[m_iCurrentMusic], m_bLoopMusic ? -1 : 1,
				500);
		m_bMusicPlaying = true;
	} else
		m_bMusicPlaying = false;

	m_bMusicWaiting = false;
}

void SoundManager::playMusic(int nr, bool bLoop)
{
	//Only startMusic if Music is enabled
	if (!Application::m_pConfig->getMusic())
		return;

	m_iCurrentMusic = nr;
	m_bLoopMusic = bLoop;
	// Music is already playing.
	// ->stop current Music
	if (m_bMusicPlaying) {
		m_bMusicWaiting = true;
		stopMusic();
	} else //if there is no Music playing. grant request
	{
		m_bMusicPlaying = true;
		m_bMusicWaiting = false;
		Mix_FadeInMusic(m_Music[m_iCurrentMusic], m_bLoopMusic ? -1 : 1,
				500);
	}
}

void SoundManager::stopMusic()
{
	Mix_FadeOutMusic(500);
}

void SoundManager::pauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::resumeMusic()
{
	Mix_ResumeMusic();
}
