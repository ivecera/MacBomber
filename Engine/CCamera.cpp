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

#include <math.h> 
#include <GLUT/glut.h>

#include "CCamera.h"
#include "CApplication.h"
#include "CConfig.h"

CCamera::CCamera()
{
	CVector3 vPosition = CVector3 ( 0.0, 0.0, 0.0 );
	CVector3 vView     = CVector3 ( 0.0, 0.0, 10.0 );
	CVector3 vUp	   = CVector3 ( 0.0, 1.0, 0.0 );
	
	m_vPosition = vPosition;	
	m_vView     = vView;		
	m_vUp	    = vUp;		
	
	
//	m_stPresets[0].vPosition = CVector3(9.5,17,13);
//	m_stPresets[0].vView = CVector3(9.5,3.65,8.7);
	
	m_stPresets[0].vPosition = CVector3(9.5,17,13); 
	m_stPresets[0].vView = CVector3(9.5,5,9); 
	m_stPresets[0].fFogStart = 20;
	m_stPresets[0].fFogEnd   = 25;

	
	m_stPresets[1].vPosition = CVector3(9.53,16.7,17);
	m_stPresets[1].vView = CVector3(9.53,4.58,10);
	m_stPresets[1].fFogStart = 22;
	m_stPresets[1].fFogEnd   = 26;


	m_stPresets[2].vPosition = CVector3(9.5,17,8.5); 
	m_stPresets[2].vView = CVector3(9.5,3.1,7.6560);
	m_stPresets[2].fFogStart = 18;
	m_stPresets[2].fFogEnd   = 25;


	m_iPreset = 0;


}
void CCamera::positionCamera( float positionX, float positionY, float positionZ, 
			      float viewX, float viewY, float viewZ,
			      float upVectorX, float upVectorY, float upVectorZ )
{

	CVector3 tmp_vPosition ( positionX, positionY, positionZ );
	CVector3 tmp_vView     ( viewX, viewY, viewZ );
	CVector3 tmp_upVector  ( upVectorX, upVectorY, upVectorZ );
	
	m_vPosition = tmp_vPosition;
	m_vView = tmp_vView;
	m_vUp	= tmp_upVector;
	
}




void CCamera::moveCamera ( float speed )
{

	/*
 	* Wir bestimmen in welche Richtung wir schauen.
 	* Dies geschieht indem wir den View Vektor vom Positions Vektor subtrahieren
 	*/
 
	CVector3 vDirection = m_vView - m_vPosition;
 
	/*
	* Wir haben den RichtungsVektor berechnet in die wir schauen.
	* Nun bewegen wir uns, in die esntsprechende Richtung indem wir die x,y,z Werte
	* des Richtungsvektors mit den entsprechenden Elmenten unsers Positionsvektor
	* multiplizieren
	*
	*/
	
	m_vPosition.x += vDirection.x * speed * CApplication::m_fReciprocalFPS;
	m_vPosition.y += vDirection.y * speed * CApplication::m_fReciprocalFPS;
	m_vPosition.z += vDirection.z * speed * CApplication::m_fReciprocalFPS;
	
	
	/*
	 * Berechnung eines neuen Viewpoints
	 */
	m_vView.x += vDirection.x * speed * CApplication::m_fReciprocalFPS;
	m_vView.y += vDirection.y * speed * CApplication::m_fReciprocalFPS;
	m_vView.z += vDirection.z * speed * CApplication::m_fReciprocalFPS;
	
	
}

void CCamera::strafeCamera ( float distance )
{
	// Die Bewegungs Richtung ist senkrecht zum Up- und View Vektor
	CVector3 vStrafeAxis =  crossProduct  ( ( m_vView - m_vPosition ), m_vUp );
	
	vStrafeAxis = normalize ( vStrafeAxis );
	
	m_vPosition.x += vStrafeAxis.x * distance *CApplication::m_fReciprocalFPS;
	m_vPosition.z += vStrafeAxis.z * distance *CApplication::m_fReciprocalFPS;
	
	m_vView.x += vStrafeAxis.x * distance *CApplication::m_fReciprocalFPS;
	m_vView.z += vStrafeAxis.z * distance *CApplication::m_fReciprocalFPS;
}

void CCamera::rotateView(float angle, float x, float y, float z)
{
	
	CVector3 vNewView;

	//Get the view vector (The direction we are facing)
	CVector3 vView = m_vView - m_vPosition;        

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	//Find the new x position for the new rotated point
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)        * vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)    * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)    * vView.z;
    	
	// Find the new y position for the new rotated point
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)    * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)        * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)    * vView.z;

    	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)    * vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)    * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)        * vView.z;

    	// Now we just add the newly rotated vector to our position to set
    	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
	
	
}

void CCamera::setViewByMouse( )
{

	// Berechnung der Fenster Mitte durch Bit Shifting
	int screenMiddleX = CApplication::screenWidth  >> 1;
	int screenMiddleY = CApplication::screenHeight >> 1; 

	// Speicheren die aktuellen Mauskoordinaten die wir mit SDL_GetMouseState(&mouseX,&mouseY) erhalten
	int mouseX;
	int mouseY;

	float angleY; // Der Winkel um den der Viewpoint um die Y-Achse rotiert werden soll
	float angleZ; // Der Winkel um den der Viewpoint um die Z-Achse rotiert werden soll
 
	
	// Wo befindet sich die Maus momentan ?
	SDL_GetMouseState( &mouseX, &mouseY );
	
	// WEnn keine Maus Bewegung stattfandt - Abbruch
	if( (mouseX == screenMiddleX) && (mouseY == screenMiddleY) ) return;
	
	// "Bewege" die Maus zurück zur Bildschirm Mitte 
	SDL_WarpMouse( screenMiddleX, screenMiddleY);                            

	/* Wir berechnen um wieviel die Maus sich in x und y Richtung bewegt hat 
	 * Durch Division wandeln wir diese Angaben in "echte" Winkel um
	 */
	angleY = ( screenMiddleX - mouseX ) / 1000.0f;
	angleZ = ( screenMiddleY - mouseY ) / 1000.0f;
	
	/* Die Achse um die der ViewPoint horizontal gedreht werden soll
	 * Diese ist senkrecht zum View- und UpVektor. Darum berechnen wir das Kreuzprodukt der 
	 * beiden Vektoren
	 */
	CVector3 vAxis = crossProduct ( ( m_vView - m_vPosition ), m_vUp ); 
	 
	// Bringe den resultierenden auf Einheitslänge ( 1 )
	vAxis = normalize ( vAxis );
	
	rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	rotateView(angleY, 0, 1, 0);


}

void CCamera::setView()
{

	gluLookAt(	m_vPosition.x, m_vPosition.y,m_vPosition.z,
				m_vView.x,m_vView.y,m_vView.z,
				m_vUp.x , m_vUp.y , m_vUp.z ); 
}



void CCamera::setPreset(int nr)
{
	m_iPreset = nr;
	m_vView = m_stPresets[nr].vView;
	m_vPosition = m_stPresets[nr].vPosition;
	
	glFogf (GL_FOG_START, m_stPresets[nr].fFogStart);
	glFogf (GL_FOG_END, m_stPresets[nr].fFogEnd);
	
}
		
 