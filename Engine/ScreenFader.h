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

#ifndef SCREENFADER_H
#define SCREENFADER_H

class ScreenFader {
private:
	int m_iAction;

	bool m_bTransitionStarted;
	bool m_bDone;
	float m_fAlpha;

	//fades from black to screen
	void fadeIn();
	//fades form screen to black
	void fadeOut();

public:
	enum enAction { FADEIN = 0, FADEOUT, NOACTION };
	ScreenFader();
	// tell screenfader what to do
	void setAction(enAction action);

	bool hasStarted();
	//returns true if current transition is done
	bool isDone();

	void update();
	void draw();
};

#endif