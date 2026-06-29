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

#ifndef HUD_H
#define HUD_H

#include <string>

using namespace std;

class Timer;
class Timebar;

class HUD {
private:
	// The x Position of the Levelname. Calculated once and stored here
	float m_fLevelName_Xpos;
	//Amount of pixels to the left/right
	float m_fMargin;

	//used for animating the "hurry up" Warning "scale in/fadeout"
	float m_fScalefactor_Warning;
	float m_fAlpha_Warning;

	// Time left
	int m_iTime;
	// The index of the current viewpoint
	int m_iView;

	//should the HUD show the time left ?
	bool m_bDrawTime;
	//shall the "Hurry up!" warning be displayed?
	bool m_bDrawWarning;
	// is HUD paused ?
	bool m_bPause;

	//methods to draw Time, "hurry up"Warning, levelname and the current view
	void drawTime();
	void drawWarning();
	void drawLevelName();
	void drawView();

	string m_strLevelName;

	Timebar *m_pTimebar;

public:
	HUD(int index);
	~HUD();
	void doDrawTime(bool bValue)
	{
		m_bDrawTime = bValue;
	};

	// gets called when game is paused
	void startPause();
	void stopPause();

	void update();
	void draw();
};

#endif
