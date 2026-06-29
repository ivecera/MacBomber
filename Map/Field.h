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

#ifndef FIELD_H
#define FIELD_H

#include <SDL3/SDL_opengl.h>

#include <glm/glm.hpp>
#include "../Objects/Bomb.h"
#include "../Objects/Crate.h"

class Item;
class Timer;
class Map;
class Explosion;
class Application;
class MeshManager;
class TextureManager;

class BoundingBox_2D;

class Field {
	/*IDEA:
	Subclasses that inherit from this class.
	They receive specific routines for events such as
	placeBomb, onEnter, etc...*/

public:
	enum state { NORMAL, BURNING, FALLING };

protected:
	char m_iType; // The type of the block (wall, field)
	int m_iTexture; // index of the fields main texture
	bool m_bColor; // the color of the field (true = color 1; false = color 2)

	bool m_bCrate; // Is there a crate on the block?
	bool m_bBomb; // Is there a bomb on the field?
	bool m_bFree; // m_bCrate + type
	bool m_bItem; // does this field has an item

	Timer m_EndOfExplosion; // End of the explosion on the field

	// Pointer to a possible bomb on the field
	Bomb *m_pBomb;
	// Pointer to a possible crate on the field
	Crate *m_pCrate;
	// Pointer to a possible item on the field
	Item *m_pItem;

	Map *m_pMap;
	// The position of the block in the block grid
	int m_iXGrid, m_iZGrid;

	Explosion *m_pExplosion;
	/*CParticleSystem * m_pItemParticleSystem;
	CParticleSystem * m_pCrateParticleSystem;*/

	// The x/y position of the min/max of the block in world space coordinates
	glm::vec3 m_vMin;
	glm::vec3 m_vMax;
	// The center of the block in world space
	glm::vec3 m_vPos;

	BoundingBox_2D *m_pBBox;

	//the amount of degree this field has to be rotated during fall
	float m_fAngle;
	// a randomly generated vector aorund which the falling field will be rotated
	glm::vec3 m_vRotationAxis;

	state m_iState;

	// Checks whether the bomb on the field has exploded
	void checkBomb();
	// Called recursively to make other fields explode
	void explodeField(int iSteps, glm::vec3 vDir, int x, int z);
	void generateItem();

	void updateItem();

public:
	Field(int xGrid, int yGrid, Map *pMap);

	virtual ~Field();

	// Places a bomb on the block
	// Returns true if a bomb could be placed (there was no bomb on the field yet)
	// Hole and Void fields always return true, since any number of bombs can be placed on them
	virtual bool placeBomb(Bomb *)
	{
		return true;
	};
	virtual void placeItem(Item *item);
	void dispatchBomb();
	void dispatchItem();

	int getType();
	Bomb *getBomb();
	Item *getItem()
	{
		return m_pItem;
	};
	Timer *getExplosionTimer()
	{
		return &m_EndOfExplosion;
	};

	void setState(state _state)
	{
		m_iState = _state;
	};
	void setTexture(int texture)
	{
		m_iTexture = texture;
	};
	virtual bool hasBomb();
	bool hasCrate();
	bool hasItem()
	{
		return m_bItem;
	};

	void setColor(bool bValue)
	{
		m_bColor = bValue;
	};
	bool getColor()
	{
		return m_bColor;
	};

	// Is the field walkable?
	bool isFree();
	bool isExploding();
	//void setExploding(bool value){ m_bExploding = value;};

	// Return the x/z coordinate of the smallest point of the bounding box
	float getMinX();
	float getMinZ();
	float getMaxX();
	float getMaxZ();
	glm::vec3 getPosition()
	{
		return m_vPos;
	};
	BoundingBox_2D *getBoundingBox()
	{
		return m_pBBox;
	};

	virtual void destroy();
	virtual void moveBomb() {};
	virtual void kickBomb(int) {};

	virtual void update() {};
	virtual void draw() {};
	virtual void drawBombs();

	// draw an eventuell explosion on this field
	void drawExplosion();
};

#endif
