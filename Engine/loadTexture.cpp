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

#include "loadTexture.h"

bool loadTexture(GLuint *texture, int index, const char *texturePath,
		 bool enableMipMap)
{
	SDL_Surface *loaded = IMG_Load(texturePath);
	if (!loaded)
		return false;

	SDL_Surface *surface =
		SDL_ConvertSurface(loaded, SDL_PIXELFORMAT_RGBA32);
	SDL_DestroySurface(loaded);
	if (!surface)
		return false;

	SDL_FlipSurface(surface, SDL_FLIP_VERTICAL);

	glGenTextures(1, &texture[index]);
	glBindTexture(GL_TEXTURE_2D, texture[index]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
		     GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	if (enableMipMap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);
	}

	SDL_DestroySurface(surface);
	return true;
}
