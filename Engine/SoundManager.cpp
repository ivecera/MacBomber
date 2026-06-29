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

SoundManager::SoundManager(MIX_Mixer *mixer)
{
	m_Samples[EXPlOSION_SOUND] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/explode.wav").c_str(),
		true);
	m_Samples[PUTBOMB_SOUND] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/putbomb.wav").c_str(),
		true);
	m_Samples[CRUNCH_SOUND] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/crunch.wav").c_str(),
		true);

	m_Music[MENU_MUSIC] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/macbomber_theme.mp3")
			.c_str(),
		false);
	m_Music[SCORESCREEN_MUSIC] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/macbomber_fanfare.mp3")
			.c_str(),
		false);
	m_Music[GAME_MUSIC] = MIX_LoadAudio(
		mixer,
		Application::expandResourcePath("/Sounds/macbomber_game.mp3")
			.c_str(),
		false);

	// create tracks for sound effects
	for (int i = 0; i < 8; i++)
		m_pSfxTracks[i] = MIX_CreateTrack(mixer);

	// create a dedicated music track
	m_pMusicTrack = MIX_CreateTrack(mixer);

	m_bMusicPlaying = false;
	m_bLoopMusic = false;
	m_bMusicWaiting = false;
	MIX_SetTrackStoppedCallback(m_pMusicTrack, SoundManager::musicDone,
				    this);
}

SoundManager::~SoundManager()
{
	MIX_StopTrack(m_pMusicTrack, 0);

	MIX_DestroyAudio(m_Samples[EXPlOSION_SOUND]);
	MIX_DestroyAudio(m_Samples[PUTBOMB_SOUND]);
	MIX_DestroyAudio(m_Samples[CRUNCH_SOUND]);

	MIX_DestroyAudio(m_Music[MENU_MUSIC]);
	MIX_DestroyAudio(m_Music[SCORESCREEN_MUSIC]);
	MIX_DestroyAudio(m_Music[GAME_MUSIC]);
}

void SDLCALL SoundManager::musicDone(void *userdata, MIX_Track *track)
{
	SoundManager *self = (SoundManager *)userdata;
	self->handelMusicDone();
}

void SoundManager::setVolumeSoundFX(int vol)
{
	// vol is 0-5, convert to float gain 0.0-1.0
	float gain = vol / 5.0f;
	for (int i = 0; i < 8; i++)
		MIX_SetTrackGain(m_pSfxTracks[i], gain);
}

void SoundManager::setVolumeMusic(int vol)
{
	// vol is 0-5, convert to float gain 0.0-1.0
	float gain = vol / 5.0f;
	MIX_SetTrackGain(m_pMusicTrack, gain);
}

void SoundManager::playSoundFX(int nr)
{
	//Only Play if Sound is enabled
	if (!Application::m_pConfig->getSoundFX())
		return;

	// find a free SFX track
	for (int i = 0; i < 8; i++) {
		if (!MIX_TrackPlaying(m_pSfxTracks[i])) {
			MIX_SetTrackAudio(m_pSfxTracks[i], m_Samples[nr]);
			MIX_PlayTrack(m_pSfxTracks[i], 0);
			return;
		}
	}
	// all tracks busy — reuse the first one
	MIX_SetTrackAudio(m_pSfxTracks[0], m_Samples[nr]);
	MIX_PlayTrack(m_pSfxTracks[0], 0);
}

void SoundManager::startMusicTrack()
{
	MIX_SetTrackAudio(m_pMusicTrack, m_Music[m_iCurrentMusic]);
	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER,
			      m_bLoopMusic ? -1 : 1);
	SDL_SetNumberProperty(props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER,
			      500);
	MIX_PlayTrack(m_pMusicTrack, props);
	SDL_DestroyProperties(props);
}

void SoundManager::handelMusicDone()
{
	if (m_bMusicWaiting) {
		startMusicTrack();
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
		startMusicTrack();
	}
}

void SoundManager::stopMusic()
{
	MIX_StopTrack(m_pMusicTrack, MIX_TrackMSToFrames(m_pMusicTrack, 500));
}

void SoundManager::pauseMusic()
{
	MIX_PauseTrack(m_pMusicTrack);
}

void SoundManager::resumeMusic()
{
	MIX_ResumeTrack(m_pMusicTrack);
}
