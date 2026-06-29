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

#include "../Defines.h"
#include "../Config.h"
#include "../Application.h"
#include "../Engine/InputManager.h"
#include "../Controller/Controller_Keyboard.h"

Controller_Keyboard::Controller_Keyboard(int ID)
	: Controller()
{
	m_iID = ID;
}

void Controller_Keyboard::update(SDL_Event &event)
{
	if (event.type == SDL_EVENT_KEY_DOWN) {
		if ((event.key.key) == Config::m_iPlayerKeys[m_iID][UP]) {
			m_bKeyHold[UP] = true;
			m_bKeyPressed[UP] = true;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][DOWN]) {
			m_bKeyHold[DOWN] = true;
			m_bKeyPressed[DOWN] = true;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][LEFT]) {
			m_bKeyHold[LEFT] = true;
			m_bKeyPressed[LEFT] = true;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][RIGHT]) {
			m_bKeyHold[RIGHT] = true;
			m_bKeyPressed[RIGHT] = true;
		} else if ((event.key.key) == Config::m_iPlayerKeys[m_iID][4]) {
			m_bKeyHold[4] = true;
			m_bKeyPressed[4] = true;
		} else if ((event.key.key) == SDLK_ESCAPE) {
			m_bKeyHold[5] = true;
			m_bKeyPressed[5] = true;
		} else if ((event.key.key) == SDLK_SPACE) {
			m_bKeyHold[6] = true;
			m_bKeyPressed[6] = true;
		}

	} else if (event.type == SDL_EVENT_KEY_UP) {
		if ((event.key.key) == Config::m_iPlayerKeys[m_iID][UP]) {
			m_bKeyHold[UP] = false;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][DOWN]) {
			m_bKeyHold[DOWN] = false;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][LEFT]) {
			m_bKeyHold[LEFT] = false;
		} else if ((event.key.key) ==
			   Config::m_iPlayerKeys[m_iID][RIGHT]) {
			m_bKeyHold[RIGHT] = false;
		} else if ((event.key.key) == Config::m_iPlayerKeys[m_iID][4]) {
			m_bKeyHold[4] = false;
		}
	}
}
