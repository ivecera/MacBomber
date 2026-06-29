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

#ifndef _loadTexture_H
#define _loadTexture_H

//#include "SDL_image.h"
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include <GLUT/glut.h>

void swap(unsigned char & a, unsigned char & b);
void flipSurface(SDL_Surface * pSurface);
bool loadTexture( GLuint *texture , int index, const char * name,bool enableMipMap = false);
SDL_Surface * convertSurface(SDL_Surface * pSurface);

#endif
