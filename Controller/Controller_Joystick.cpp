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

#include "Controller_Joystick.h"
#include "Application.h"
#include "InputManager.h"

#include "Defines.h"

Controller_Joystick::Controller_Joystick(int ID, SDL_Joystick *pJoystick)
	: Controller()
{
	m_iID = ID;
	m_iDeadZone = 3200;
	m_pJoystick = pJoystick;
}

Controller_Joystick::~Controller_Joystick()
{
	if (SDL_JoystickOpen(SDL_JoystickIndex(
		    m_pJoystick))) //needed to prevent crash.... (?)
		SDL_JoystickClose(m_pJoystick);
}

void Controller_Joystick::update(SDL_Event &event)
{
	// --- register one time "keydown" events

	//check for joystick axes events
	if ((event.type == SDL_JOYAXISMOTION) &&
	    (event.jaxis.which == (m_iID - 4))) {
		//ignore events, which are within the joysticks deadzone
		if ((event.jaxis.value < (-1 * m_iDeadZone)) ||
		    (event.jaxis.value > m_iDeadZone)) {
			//event occured on joysticks x-axis (left/right)
			if (event.jaxis.axis == 0) {
				if (event.jaxis.value > 0)
					m_bKeyPressed[RIGHT] = true;
				else
					m_bKeyPressed[LEFT] = true;
			}

			//event occured on joysticks y-axis (up/down)
			if (event.jaxis.axis == 1) {
				if (event.jaxis.value > 0)
					m_bKeyPressed[UP] = true;
				else
					m_bKeyPressed[DOWN] = true;
			}
		}
	}

	// has button 0 (bomb button) been pressed down ?
	if ((event.type == SDL_JOYBUTTONDOWN) &&
	    (event.jbutton.which == (m_iID - 4)) &&
	    (event.jbutton.button == 0)) {
		m_bKeyPressed[4] = true;
	}

	// has button 0 (bomb button) been released down ?
	if ((event.type == SDL_JOYBUTTONUP) &&
	    (event.jbutton.which == (m_iID - 4)) &&
	    (event.jbutton.button == 0)) {
	}

	for (int i = 0; i < 7; i++)
		m_bKeyHold[i] = false;

	// --- check wether a key is hold

	if (SDL_JoystickIndex(m_pJoystick) == (m_iID - 4)) {
		int value;
		value = SDL_JoystickGetAxis(m_pJoystick, 1);

		if (value > m_iDeadZone)
			m_bKeyHold[DOWN] = true;
		else if (value < (-1 * m_iDeadZone))
			m_bKeyHold[UP] = true;

		value = SDL_JoystickGetAxis(m_pJoystick, 0);
		if (value > m_iDeadZone)
			m_bKeyHold[RIGHT] = true;
		else if (value < (-1 * m_iDeadZone))
			m_bKeyHold[LEFT] = true;
	}
}
