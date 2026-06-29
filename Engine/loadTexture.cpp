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

#include <string.h>
#include "loadTexture.h"
#include "SDL/SDL_endian.h"

void swap(unsigned char & a, unsigned char & b)
{
    unsigned char temp;
	
    temp = a;
    a    = b;
    b    = temp;
	
    return;
}


// IMG_Load loads images vertically mirrored. We flip this surface... 
void flipSurface(SDL_Surface * pSurface)
{
	int BytesPerPixel = pSurface->format->BytesPerPixel ; 
	int width  = pSurface->w;
    int height = pSurface->h;
	//  one char == one Byte
    unsigned char * data = (unsigned char *) (pSurface->pixels);         // the pixel data
	
	SDL_LockSurface( pSurface );
	
	for( int i = 0 ; i < (height / 2) ; ++i )
        for( int j = 0 ; j < width * BytesPerPixel; j += BytesPerPixel )
            for(int k = 0; k < BytesPerPixel; ++k)
                swap( data[ (i * width * BytesPerPixel) + j + k], data[ ( (height - i - 1) * width * BytesPerPixel ) + j + k]);
	
	SDL_UnlockSurface( pSurface );
}

SDL_Surface * convertSurface(SDL_Surface * surface)
{
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;
	
    /* Use the surface width and height expanded to powers of 2 */
    w = surface->w;
    h = surface->h;

    image = SDL_CreateRGBSurface(
								 SDL_SWSURFACE,
								 w, h,
								 32,
#if (SDL_BYTEORDER == SDL_LIL_ENDIAN) /* OpenGL RGBA masks */
								 0x000000FF,
								 0x0000FF00,
								 0x00FF0000,
								 0xFF000000
#else
								 0xFF000000,
								 0x00FF0000,
								 0x0000FF00,
								 0x000000FF
#endif
								 );
    if ( image == NULL ) {
        return 0;
    } /* Save the alpha blending attributes */
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, 0, 0);
    }

    /* Copy the surface into the GL texture image */
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, image, &area);

    /* Restore the alpha blending attributes */
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }
	SDL_FreeSurface(surface);
    return image;
}

bool loadTexture( GLuint *texture , int index, const char * texturePath, bool enableMipMap )
{
	// Status indicator 
	bool Status = false;
	
	
	// Create storage space for the texture 
	SDL_Surface * pTexture;
	SDL_Surface * _pTexture;
	
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit 
	if ( ( pTexture = IMG_Load( texturePath ) ) )
	{
		_pTexture = convertSurface(pTexture);
		flipSurface(_pTexture);
		// Set the status to true 
		Status = true;
		
		glGenTextures( 1, &texture[index] );		
		glBindTexture( GL_TEXTURE_2D, texture[index] );
		
		if (enableMipMap)
		{
			
			//Mip Mapping 
			 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
			 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			 gluBuild2DMipmaps(GL_TEXTURE_2D, 4,_pTexture->w,_pTexture->h, GL_RGBA, GL_UNSIGNED_BYTE, _pTexture->pixels);
		}
		else
		{	// Linear Filtering (slow but looks good)
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, _pTexture->w,
						  _pTexture->h, 0, GL_RGBA,
						  GL_UNSIGNED_BYTE, _pTexture->pixels );
			
			
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	// Free up any memory we may have used 
	if ( pTexture )
		SDL_FreeSurface( _pTexture );
	
	
	return Status;
}

/*
bool loadTexture( GLuint *texture , int index, char * name )
{
	// Status indicator 
	bool Status = false;

	char texturePath[150]="/Users/quarus/Entwicklung/Textures/";
	strcat(texturePath,name);

	// Create storage space for the texture 
	SDL_Surface * pTexture;
	SDL_Surface * _pTexture;
	
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit 
	if ( ( pTexture = IMG_Load( texturePath ) ) )
	{
		_pTexture = convertSurface(pTexture);
		flipSurface(_pTexture);
		// Set the status to true 
		Status = true;
		
		glGenTextures( 1, &texture[index] );		
		glBindTexture( GL_TEXTURE_2D, texture[index] );
		
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, _pTexture->w,
					  _pTexture->h, 0, GL_RGBA,
					  GL_UNSIGNED_BYTE, _pTexture->pixels );
		
		// Linear Filtering 
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	// Free up any memory we may have used 
	if ( pTexture )
		SDL_FreeSurface( _pTexture );

	return Status;
}*/