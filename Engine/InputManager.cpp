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

/*People demand freedom of speech as a compensation
for the freedom of thought which they never use - Kierkegaard
 */
#include "InputManager.h"
#include "../Controller/Controller_Keyboard.h"
#include "../Controller/Controller_Joystick.h"

InputManager::InputManager()
{
	// Inititate Controllers
	for (int i = 0; i < 8; i++)
		m_pController[i] = NULL;

	//---- Keyboard Controllers
	for (int i = 0; i < 4; i++)
		m_pController[i] = new Controller_Keyboard(i);

	//---- Joystick Controllers
	SDL_SetJoystickEventsEnabled(true);
	int numJoysticks = 0;
	SDL_JoystickID *joysticks = SDL_GetJoysticks(&numJoysticks);
	m_iJoystickCount = numJoysticks;
	//Restrict to 4 Joysticks at most
	if (m_iJoystickCount > 4)
		m_iJoystickCount = 4;
	SDL_Log("InputManager: Found %d joystick(s)", m_iJoystickCount);

	for (int i = 0; i < m_iJoystickCount; i++) {
		m_pController[4 + i] = new Controller_Joystick(
			4 + i, SDL_OpenJoystick(joysticks[i]));
	}
	SDL_free(joysticks);

	// some joysticks or SDL seem to produce bogus events after being opened
	// (stolen from supertux)
	Uint64 ticks = SDL_GetTicks();
	while (SDL_GetTicks() - ticks < 500) {
		SDL_Event event;
		SDL_PollEvent(&event);
	}
}

InputManager::~InputManager()
{
	for (int i = 0; i < 8; i++)
		delete m_pController[i];
}

bool InputManager::joysticksPresent()
{
	if (m_iJoystickCount > 0)
		return true;
	else
		return false;
}

bool InputManager::isJoystickPresent(int joystickID)
{
	if (joystickID >= 0 && joystickID < m_iJoystickCount &&
	    m_pController[4 + joystickID] != NULL)
		return true;
	else
		return false;
}

Controller *InputManager::getController(int ctrlID)
{
	if (m_pController[ctrlID] == NULL) {
		SDL_Log("InputManager: Null Controller requested!");
		return m_pController[0];
	} else
		return m_pController[ctrlID];
}

void InputManager::dispatchEvent(SDL_Event &event)
{
	for (int i = 0; i < 4 + m_iJoystickCount; i++)
		m_pController[i]->update(event);
}

void InputManager::resetAll()
{
	for (int i = 0; i < 4 + m_iJoystickCount; i++)
		m_pController[i]->reset();
}
