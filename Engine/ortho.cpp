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

#include <SDL3/SDL_opengl.h>
#include "MatrixStack.h"
#include "ortho.h"
#include "../Application.h"
#include "../Config.h"

void enableOrthoMode()
{
	projection.push();
	projection.load(glm::ortho(0.0f, (float)Application::screenWidth, 0.0f,
				   (float)Application::screenHeight, -100.0f,
				   100.0f));
	projection.apply();

	glNormal3f(0, 0, 1);

	modelview.push();
	modelview.loadIdentity();
	modelview.apply();
}

void disableOrthoMode()
{
	projection.pop();
	projection.apply();

	modelview.pop();
	modelview.apply();
}

float relToAbs(float relValue, int axis)
{
	//axis = 0 -> x
	//axis = 1 -> y
	if (axis > 0)
		return (Application::screenHeight * relValue);
	else
		return (Application::screenWidth * relValue);
}

float absToRel(float absValue, int axis)
{
	// FIX ME : check for division by 0
	if (axis > 0)
		return (absValue / Application::screenHeight);
	else
		return (absValue / Application::screenWidth);
}
