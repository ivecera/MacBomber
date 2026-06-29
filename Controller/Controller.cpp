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

#include "Controller.h"
#include "Defines.h"

Controller::Controller()
{
	for (int i = 0; i < 7; i++) {
		m_bKeyHold[i] = false;
		m_bKeyPressed[i] = false;
	}
}

Controller::~Controller()
{
}

void Controller::reset()
{
	for (int i = 0; i < 7; i++)
		m_bKeyPressed[i] = false;
}

bool Controller::isUpPressed()
{
	return m_bKeyPressed[UP];
}

bool Controller::isDownPressed()
{
	return m_bKeyPressed[DOWN];
}

bool Controller::isLeftPressed()
{
	return m_bKeyPressed[LEFT];
}

bool Controller::isRightPressed()
{
	return m_bKeyPressed[RIGHT];
}

bool Controller::isBombPressed()
{
	return m_bKeyPressed[4];
}

bool Controller::isSpacePressed()
{
	return m_bKeyPressed[6];
}

bool Controller::isBackPressed()
{
	return m_bKeyPressed[5];
}

bool Controller::isUpHold()
{
	return m_bKeyHold[UP];
}

bool Controller::isDownHold()
{
	return m_bKeyHold[DOWN];
}

bool Controller::isLeftHold()
{
	return m_bKeyHold[LEFT];
}

bool Controller::isRightHold()
{
	return m_bKeyHold[RIGHT];
}
