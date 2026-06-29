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
#include "Defines.h"
#include "../Application.h"
#include "Camera.h"
#include "Controller_Keyboard.h"
#include "Controller_Joystick.h"
#include "../Config.h"
#include "Init.h"

InputManager::InputManager(Application *pApp)
{
	m_pApp = pApp;

	// Inititate Controllers
	for (int i = 0; i < 8; i++)
		m_pController[i] = NULL;

	//---- Keyboard Controllers
	for (int i = 0; i < 4; i++)
		m_pController[i] = new Controller_Keyboard(i);

	//---- Joystick Controllers
	SDL_JoystickEventState(SDL_ENABLE);
	m_iJoystickCount = SDL_NumJoysticks();
	//Restrict to 4 Joysticks at most
	if (m_iJoystickCount > 4)
		m_iJoystickCount = 4;
	printf("InputManager: Found %d joystick(s)\n", m_iJoystickCount);

	for (int i = 0; i < m_iJoystickCount; i++) {
		m_pController[4 + i] =
			new Controller_Joystick(4 + i, SDL_JoystickOpen(i));
	}

	// some joysticks or SDL seem to produce bogus events after being opened
	// (stolen from supertux)
	Uint32 ticks = SDL_GetTicks();
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
	if (SDL_JoystickOpened(joystickID))
		return true;
	else
		return false;
}

Controller *InputManager::getController(int ctrlID)
{
	if (m_pController[ctrlID] == NULL) {
		printf("InputManager: Null Controller requested!\n");
		return m_pController[0];
	} else
		return m_pController[ctrlID];
}

void InputManager::update()
{
	SDL_Event event;
	m_pKeystate = SDL_GetKeyState(NULL);

	for (int i = 0; i < 8; i++) {
		if (m_pController[i] != NULL)
			m_pController[i]->reset();
	}

	while (SDL_PollEvent(&event)) {
		//send current event to controller classes
		for (int i = 0; i < 8; i++) {
			if (m_pController[i] != NULL)
				m_pController[i]->update(event);
		}

		switch (event.type) {
		case SDL_QUIT:
			SDL_Quit();
			break;
		case SDL_KEYDOWN:

			// Iteriere durch Tasten bei denen Tastenwiederholung
			// unerw¬∏nscht ist
			switch (event.key.keysym.sym) {
			case SDLK_1:
				m_pApp->m_pCamera->setPreset(0);
				break;
			case SDLK_2:
				m_pApp->m_pCamera->setPreset(1);
				break;
			case SDLK_3:
				m_pApp->m_pCamera->setPreset(2);
				break;

				/*					case SDLK_4:
						m_pApp->m_pCamera->setPreset(3);
						break;*/

			case SDLK_p:
				m_pApp->pause();
				break;
				/*					
					case SDLK_t:
						dumpScreen();
						break;
				
					case SDLK_z:
						printf("pos: %f, %f, %f\n", 
							m_pApp->m_pCamera->m_vPosition.x,
							m_pApp->m_pCamera->m_vPosition.y,
							m_pApp->m_pCamera->m_vPosition.z);
						printf("view: %f, %f, %f\n", 
							m_pApp->m_pCamera->m_vView.x,
							m_pApp->m_pCamera->m_vView.y,
							m_pApp->m_pCamera->m_vView.z);
						break;
							*/
			default:
				break;

			} // switch( event.key.keysym.sym)
			break;

		default:
			break;
		} //switch ( event.type )

	} //while

	if (m_pKeystate[SDLK_a] == SDL_PRESSED) {
		m_pApp->m_pCamera->strafeCamera(-1.0f);
	}

	if (m_pKeystate[SDLK_w] == SDL_PRESSED) {
		m_pApp->m_pCamera->moveCamera(1.0f);
	}

	if (m_pKeystate[SDLK_d] == SDL_PRESSED) {
		m_pApp->m_pCamera->strafeCamera(1.0f);
	}

	if (m_pKeystate[SDLK_s] == SDL_PRESSED) {
		m_pApp->m_pCamera->moveCamera(-1.0f);
	}
}