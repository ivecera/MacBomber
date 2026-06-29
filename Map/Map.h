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

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <list>
#include <GLUT/glut.h>

class Object;

#include "Vector3.h"
#include "BoundingBox_2D.h"
#include "StMapEntry.h"
#include "../Defines.h"
#include "Timer.h"
#include "../Engine/ParticleSystem/ParticleManager.h"
#include "3DMath.h"

using namespace std;

class Object_Moving;
class Player;
class Field;
class Bomb;
class BombThrower;
class ItemThrower;
class Item;
class Shaker;
class Application;
class Game;

class Map {
	struct pos2D {
		int x;
		int z;
	};

	int m_iPlayerCount; //Anzahl der Spielerstartpunkte in der Map
	pos2D m_StPlayerStartPos[8]; // Die Position der Spielerstartpunkte

	// Die Grösse des Spielfeldes in Blöcken
	int m_iWidth;
	int m_iHeight;

	//the amount of fields, which are *non void* (needed for MapDestroyer & Itemthrower)
	int m_iFieldCount;
	char *name;

	/* Stores the map
	 *			19
	 * O------------------x
	 * |
	 * |	
	 * |
	 * |	
	 * | 15
	 * |
	 * z
	 *		   .
	 *		camera
	 */

	Field *m_pMap[19][15];

	Timer m_ShakeTimer;
	Shaker *m_pShaker;
	// this bombthrower is used to manage flying bombs
	// all holes of this map put their bomb into this thrower
	BombThrower *m_pBombThrower;

	// itemmanager used to manage flying items
	// players put items in it, when they die
	ItemThrower *m_pItemThrower;

	// only true if this map actually has an bombthrower
	// ( == if there is at least one hole)
	bool m_bBombThrower;

	//used to move the map slightly to the specified direction
	//caused a "shake" effect
	Vector3 m_vDisplacement;

	Application *m_pApp;
	Game *m_pGame;

	// this fields contains pointers to all falling fields
	list<Field *> m_listFallingFields;

	list<Field *> m_listCrateFields;
	list<Field *> m_listBlockFields;

	list<Field *> m_listPlainFields_Color0;
	list<Field *> m_listPlainFields_Color1;

	list<Field *> m_listArrowFields_Color0;
	list<Field *> m_listArrowFields_Color1;

	list<Field *> m_listHoleFields_Color0;
	list<Field *> m_listHoleFields_Color1;

	list<Field *> m_listBombFields;
	list<Field *> m_listItemFields;
	list<Field *> m_listExplodingFields;

	void drawCrateFields();
	void drawBlockFields();
	void drawPlainFields();
	void drawArrowFields();
	void drawHoleFields();

	void drawBombs();
	void drawItems();

	//calculates a displacement vector with length 1
	//It does this by calculating a point on sphere around (0,0,0) with radius 1
	void calculateDisplacement(Vector3 &vDisplacement);

	// deletes all field in the array m_pMap
	void cleanUp();

public:
	static int m_iBombsOnField[4];
	ParticleManager m_ParticleManager;

	Map(Game *pGame, int mapIndex);
	~Map();

	// Initialisiert das Field Spielfeld Array in Abhängigkeit vom übergebenen Char Array
	void init();

	bool hasBomb(int x, int z);
	bool hasItem(int x, int z);
	bool hasCrate(int x, int z);
	bool hasPlayer(int x, int z);

	// returns the type of field at x,z
	int getType(int x, int z);

	// returniert true wenn auf dem entsprechendem Feld kein Block / Crate / Bombe steht
	bool isFree(int x, int z);

	//platziert auf dem spezifizierten Feld die Bombe bomb
	bool placeBomb(Bomb *bomb);
	void dispatchBomb(int x, int z);
	void placeItem(Item *item);
	void dispatchItem(int x, int z);

	// wird aufgerufen eine Explosion des entsprechenden Block erreicht
	void destroyBlock(int x, int z);

	// Überprüft, ob der Spieler auf einem Feld ist, das gerade explodiert
	bool doesBurn(Player *player);
	// Überprüft, ob das spezifizierte Feld gerade explodiert
	bool doesBurn(int x, int z);

	Bomb *getBomb(int x, int z);
	Item *getItem(int x, int z);

	int getPlayerStartPositionX(int nr);
	int getPlayerStartPositionZ(int nr);

	int getHeight()
	{
		return m_iHeight;
	};
	int getWidth()
	{
		return m_iWidth;
	};
	int getFieldCount()
	{
		return m_iFieldCount;
	};

	//checks if player collides with a block/crate
	//if yes: returns true,direction in which player should slide (if necessary) and time of collision
	bool doesPlayerCollide(Player *pPlayer, Vector3 &slideDirection,
			       float &time);

	// let the specified field drop
	void doDrop(int x, int z);

	// adds a bomb to the bombthrower
	void addBombToThrower(Vector3 vStart, Bomb *pBomb);
	//add item to the itemthrower
	void addItemToThrower(Vector3 vStart, Item *pItem);

	//sorts a given field into to the matching drawlist
	void sortField(Field *pField);

	// draws the map
	void draw();
	//draws all current explosions
	void drawExplosions();

	//shakes the map for 300 ms
	void doShake();
	void update();
};

#endif
