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

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "SDL/SDL.h"

class Application;
class Controller;

class InputManager {
private:
	int m_iJoystickCount;
	Uint8 *m_pKeystate;

	Application *m_pApp;
	Controller *m_pController[8];

public:
	InputManager(Application *pApp);
	~InputManager();

	Controller *getController(int ctrlID);

	//returns count of connected joysticks
	int getJoystickCount()
	{
		return m_iJoystickCount;
	};

	//returns true if there are any joysticks present;
	bool joysticksPresent();
	//returns true if joystick with SDL ID joystickID is present
	bool isJoystickPresent(int joystickID);

	//queries joystick events
	void update();
};

#endif
