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

#ifndef CCAMERA
#define CCAMERA


#include "CVector3.h"
#include "3DMath.h"
#include "SDL/SDL.h"



/** Diese Klasse repäsentiert die virtuelle Kamera in der 3D Welt
  *
  *
  */

struct stPreset
{
	// Cameras position
	CVector3 vPosition;
	
	// the coordinate the camera is looking at
	CVector3 vView;	
	// since we have changing views (&use OpenGL fog) we store for each preset fog start/end values seperately
	float fFogStart;
	float fFogEnd;
	
};

class CCamera
{
private:
	
	// Vordefinierte Werte fŸr Kameraeinstellung
	stPreset m_stPresets[3];
	
	//index of our currently uses preset
	int m_iPreset;

	public:
		CVector3 m_vPosition;	// Die Position der virtuellen Kamera
		CVector3 m_vView;	// Die Blickrichtung der virtuellen Kamera
		CVector3 m_vUp;		// Die Richtung, welche "Oben" definiert
		// FIXME: LEft Vektor 
		
		CCamera();	
		
		/** Positioniert die Kamera in der virtuellen Welt
		 * \param positionX,positionY,positionZ Die Position der Kamera in der Welt
		 * \param viewX,viewY,viewZ Der Vektor in die die Kamera blickt
		 * \param upVectorX,upVectorY,upVectorZ Der Vektor beschreibt welche Richtung "oben" ist
		 */
		
		void positionCamera( float positionX, float positionY, float positionZ, 
				float viewX, float viewY, float viewZ,
				float upVectorX, float upVectorY, float upVectorZ );
		
		/** Bewegt die Kamera durch die virtuelle Welt Vor- und Rückwärts
		 *
		 * \param distance Der Betrag um den die Kamera bewegt werden soll
		 *
		 */
		 
		void moveCamera ( float distance ); //bewegt die Kamera um den Betrag "distance"
		
		
		/** Straft die Camera um den Betrag Distance nach links bzw. rechts
		 *  \param distance Der Betrag um den die Kamera gestraft werden soll
		 *
		 */
		void strafeCamera ( float distance );
		
		/** Rotiert die Kamera um die Achse (x,y,z)
		 * 
		 * \param angle Der Winkel um den rotiert werden soll
		 * \param x,y,z Definieren die Achse um die gedreht werden soll
		 *
		 */
		void rotateView(float angle, float x, float y, float z);
		
		
		void setViewByMouse ( );
		void setView();

		void setPreset(int nr);
		int getPreset(){return m_iPreset;};
		
		
	
};
 
 
#endif