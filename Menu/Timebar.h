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

#ifndef TIMEBAR_H
#define TIMEBAR_H

#include "../Engine/Vector3.h"

// our timebar has always a fix length
class Timebar {
private:
	/* four vertices of the timebar rectangle
	  0 --------------- 1
	  |					|
	  3 --------------- 2
	*/
	Vector3 m_vVertices[4];
	// Texcoord of vertices 1 and 2
	float m_fTexCoordX;
	// specifies by what (pixel)amount the timebar should shrink per second
	float m_fStepPerSecond;
	/*	specifies by what (pixel)amount the texcoord of timebar vertices 1 and 2
		should shrink per second*/
	float m_fStepPerSecond_Tex;

public:
	Timebar(int totalTime);

	//update timebar when "time" seconds are remaining
	void update(int time);
	void draw();
};
#endif
