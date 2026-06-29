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

#ifndef DMath_H
#define DMath_H

#include "CVector3.h"

/// berechnet das Kreuzprodukt zweier Vekoren
CVector3 crossProduct ( const CVector3 &u, const CVector3 &v );
      
/** berechnt das Dot Produkt zweier Vekoren
 *
 *  \param u,v die Vekoren deren DotProduct gebildet werden soll
 *  \return Das DotProduct von u und v
 */
float dotProduct ( const CVector3 &u, const CVector3 &v );


/** brechnet die Länge des Vektors v
 *
 * \return Die Länge des Vektors v
 *
 */
float magnitude ( const CVector3 &v );

/** Berechnet den Einheitsvektor ( Einen Vektor mir selber Richtung aber Länge eins )
 * \param v Der zu normalisierende Vektor
 * \return Der normalisierte Vektor
 *
 */
CVector3 normalize (  CVector3 &v );

//rotates a given point in the x/z plane around the y axis
void rotateAroundYAxis(float &x,float &z, float theta);


#endif
