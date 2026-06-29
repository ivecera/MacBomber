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

#ifndef CBomb_H
#define CBomb_H

#include <GLUT/glut.h>
#include <iostream.h>
#include "SDL/SDL.h"


#include "../Defines.h"
#include "CObject_Moving.h"
#include "CTimer.h"


class CBomb : public CObject_Moving
{
protected:

	int m_iOwnerID;
	int m_iBombID;
	bool m_bOwnerLeft;
	
    // Ist die Bombe explodiert ?
    // Diese Variable ist wichtig für das Vorgehen im Bombmanager
    bool m_bExploded;

	
    // Die maximale Explosions"radius" der Bombe in Feldern
    int m_iStrength;
    
    // Die folgenden Werte geben an, wieviele Felder von der Bombe bzgl. der 4 möglichen Explosionrichtungen
    // erfasst werden
    int m_iRadius[4];
    
    // Der Zeitpunkt an dem die Bombe explodiert
	float m_fExplosionTime;
	
public:
	
	static int m_iBombNr;

	CTimer m_StartExplosionTimer;
	
    // Übergeben werden Position, Besitzer und Stärke der Bombe
    CBomb( int xBlock, int zBlock, int owner, int strength );
	
    // setzt m_bExploded auf true; 
    void explode();
	
    // returniert, ob die Bombe explodiert ist
    bool isExploded();
    int getStrength();

	int getOwnerID(){return m_iOwnerID;};
	int getBombID(){return m_iBombID;};

	bool hasOwnerLeft(){return m_bOwnerLeft;};
	void setOwnerLeft(bool b){ m_bOwnerLeft = b;};
    
  	
    // returniert true falls die Bombe sich bewegt
    bool doesMove();
    // stoppt die Bewegung
    void stopMovement();
    
	void update();
	void draw();
    
};



#endif;