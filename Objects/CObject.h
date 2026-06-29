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

#ifndef CObject_H
#define CObject_H


#include "CVector3.h"
#include "CBoundingBox_2D.h"

/*
 * Diese Klasse beschreibt ein Objekt auf dem Spielfeld.
 * Ein Objekt kann ein Spieler oder eine Bombe sein
 *
 */

class CWobbler;

class CObject
{

protected:
    
	//what kind of object is this ? 
	int m_iType;
	
	
    // Die Position des Objekts auf dem Spielfeld in Blöcken 
    int m_xBlock;
    int m_zBlock;
    
    CVector3 m_vPos;	// Die Position des Objektmittelpunkts auf dem Spielfeld in World Koordinaten 
    float m_fSize;		// Die Seitenlänge des Objekts

	CBoundingBox_2D * m_pBBox;
	
	// m_pWobbbler is used to scale the object on up to 3 axis, thus causing a "wobbling" effect
	bool m_bWobble;		//true if Object should "wobble"
	CWobbler * m_pWobbler;
	
public:
    
    // Dem konstruktor werden folgende Werte übergeben:
    //      xBlock  -   die x Position des Objekts in Blockkoordinaten
    //      zBlock  -   die z Position des Objekts in Blockkoordinaten
    //      size    _   die Länge der Bounding Box des Objekts  ( Default = 1 )
        
    CObject( int xBlock, int zBlock, float size = 1.0f );
	virtual ~CObject();
    
	int getXBlock();
    int getZBlock();
	
	int getType(){return m_iType;};
	float getSize();
	void setPosition(CVector3 vPos);
    CVector3 getPosition();
	CBoundingBox_2D * getBoundingBox();
	
	// überprüft, ob dieses Objekt mit einem anderen kollidiert
	bool doesCollideWith(CObject * pObject);
	
	void setWobble(bool bWobble);
    virtual void draw() = 0;	

};

#endif