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

#include "3DMath.h"
#include <SDL3/SDL.h>

void rotateAroundYAxis(float &x, float &z, float theta)
{
	float _x;
	float _z;
	//convert deg -> rad
	theta = (theta * SDL_PI_F / 180);

	_x = ((SDL_cosf(theta) * x) + (SDL_sinf(theta) * z));
	_z = ((-1 * SDL_sinf(theta) * x) + (SDL_cosf(theta) * z));

	x = _x;
	z = _z;
}
