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

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL_mixer/SDL_mixer.h"

class SoundManager {
private:
	//stores our sound FX
	Mix_Chunk *m_Samples[3];
	//stores our music
	Mix_Music *m_Music[3];
	// currently playing music

	int m_iCurrentMusic;
	//true, if music is currently playing
	bool m_bMusicPlaying;
	//true, if (waiting) music has to be looped
	bool m_bLoopMusic;
	//true if a another music track is waiting, for current music to fadeout
	bool m_bMusicWaiting;

	// Expands a given path with root "Contents/Resource" to absolute System Path
	const char *expand(char *path);

	/* 
	 * void musicDone() is a callback function needed for SDLs Mix_HookMusicFinished call.
	 * What musicDone does is, to get the soundmanagers Address via Application::m_pSoundManager
	 * and to call another element function "handelMusicDone()", where the real action takes place.
	 */
	static void musicDone();

public:
	SoundManager();
	~SoundManager();

	void setVolumeSoundFX(int vol);
	void setVolumeMusic(int vol);

	//plays sound, specified by nr
	void playSoundFX(int nr);

	//gets called when a music is done playing
	void handelMusicDone();

	//Play Music, which is specified by nr. bLoop specifies if track should be looped
	void playMusic(int nr, bool bLoop = true);
	void stopMusic();

	void pauseMusic();
	void resumeMusic();

	bool isMusicPlaying()
	{
		return m_bMusicPlaying;
	};
};

#endif
