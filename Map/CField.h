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

#ifndef CField_H
#define CField_H

#include <GLUT/glut.h>

#include "CVector3.h"
#include "../Objects/CBomb.h"
#include "../Objects/CCrate.h"


class CItem;
class CTimer;
class CMap;
class CExplosion;
class CApplication;
class CMeshManager;
class CTextureManager;

class CBoundingBox_2D;

class CField
{
    /*IDEE:
	Oberblöcke, die von dieser Klasse erben.
	Sie erhalten dann spezifische Routinen für Ereignisse, wie Z.b
	Placebomb, onenter, etc...*/  

public:
	enum state{NORMAL,BURNING,FALLING};

protected:
    

    
    char m_iType;		// Die Typ des Blocks ( Mauer, Feld )
	int m_iTexture;		// index of the fields main texture
	bool m_bColor;		// the color of the field (true = color 1; false = color 2) 
	
    bool m_bCrate;		// Steht auf dem Block eine Kiste ?
	bool m_bBomb;		// Steht auf dem Feld eine Bombe ?
	bool m_bFree;		// m_bCrate + Typ
    bool m_bItem;		// does this field has an item  
	
	
	CTimer m_EndOfExplosion;	// Ende der Expolsion auf dem Feld
	
    // Pointer zu einer eventuellem Bombe, die auf dem Feld steht
    CBomb * m_pBomb;
    // Pointer zu einem eventuellen Crate, das auf dem Feld steht
    CCrate * m_pCrate;
    // Pointer zu einem eventuellen Item, das auf dem Feld steht
    CItem  * m_pItem;

	CMap * m_pMap;
    // Die Postion des Blocks im Block Gitter
    int m_iXGrid, m_iZGrid;

	CExplosion * m_pExplosion;
	/*CParticleSystem * m_pItemParticleSystem;
	CParticleSystem * m_pCrateParticleSystem;*/

    // Die x/y Position des Minimus / Maximus des Blocks in Worldspace Koordinaten
    CVector3 m_vMin;
    CVector3 m_vMax;
    // Die Mitte des Blocks im Worldspace
    CVector3 m_vPos;
	
	CBoundingBox_2D * m_pBBox;

	//the amount of degree this field has to be rotated during fall 
	float m_fAngle;
	// a randomly generated vector aorund which the falling field will be rotated
	CVector3 m_vRotationAxis;
	
	state m_iState;
	
	// Überprüft, ob die auf dem Feld vorhandene Bombe explodiert
	void checkBomb();	
	// wird rekursiv aufgerufen, um andere Felder zum explodieren zu bringen
	void explodeField(int iSteps, CVector3 vDir, int x, int z);	
	void generateItem();
	
	
	void updateItem();
	

public:

    CField( int xGrid, int yGrid, CMap * pMap );
  
    virtual ~CField();
    
    
	// platziert eine Bombe auf den Block
    // returniert true, falls eine Bombe platziert werden konnte (es befand sich noch keine Bombe auf dem entsprechenden Feld)
	// Hole- und Void Felder returnieren immer true, da man bel. viele Bomben auf ihnen platzieren kann
    virtual bool placeBomb ( CBomb * bomb ){return true;};
	virtual void placeItem ( CItem * item );
    void dispatchBomb();
	void dispatchItem();
	
    int getType();
    CBomb * getBomb();
	CItem * getItem(){return m_pItem;};
	CTimer * getExplosionTimer(){return &m_EndOfExplosion;};
    
	void setState(state _state){m_iState = _state;};
	void setTexture(int texture){m_iTexture = texture;};
    virtual bool hasBomb();	
    bool hasCrate();
	bool hasItem(){return m_bItem;};
	
	void setColor(bool bValue){m_bColor = bValue;};
	bool getColor(){return m_bColor;};

    // ist das Feld begehbar ?
    bool isFree();
	bool isExploding();
	//void setExploding(bool value){ m_bExploding = value;}; 
    
    // returnieren die x/z Koordinate des kleinsten Punktes der BoundingBox
    float getMinX();
    float getMinZ();
    float getMaxX();
    float getMaxZ();
	CVector3 getPosition(){return m_vPos;};
	CBoundingBox_2D * getBoundingBox(){return m_pBBox;};
	
	virtual void destroy();
	virtual void moveBomb(){};
	virtual void kickBomb(int dir){};
	
	virtual void update(){};
    virtual void draw(){};
	virtual void drawBombs();
	
	// draw an eventuell explosion on this field 
	void drawExplosion();
};    



#endif
