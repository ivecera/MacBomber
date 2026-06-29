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

#ifndef CTriangle_H
#define CTriangle_H

#include "CVector3.h";

// Daten die per Dreieck angegeben werden
class CTriangle
{
public:
    // Jedes Dreieck hat drei Punkte ( vektoren )
    int nVertex[3];
    
    CVector3 * pVertex[3];
    
    // die jeweils eine x,y Tekturkoordinate haben
    float texCoordX[3];
    float texCoordY[3];
	
    // Die Index Nummer des Materials der Surface 
    int nMaterial;
    
	
	// Die folgenden zwei Infos werden nicht benötigt, da die Info im Material steckt
    // Ist dieses Dreieck Texturiert
    bool bTexture;
    // Die Index Nummer der Texture
    int iTextureIndex;   
	
    
    // Der Mittelpunkt des Dreiecks
    CVector3 vMiddle;
    
    // Der NormalVektor des Dreiecks
    CVector3 vNormal;
    
    // Der Abstand der vom Dreieck aufgespannten Fl√§che zum Ursprung
    float distanceToOrigin;
};

#endif;
