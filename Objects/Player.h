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

#ifndef Player_H
#define Player_H

#include "../Map/Map.h"
#include "Object_Moving.h"
#include "Bomb.h"
#include "../Defines.h"
#include "../Controller/Controller_Keyboard.h"

class Item;
class ItemManager;
class Timer;

class Player : public Object_Moving {
	// Die Goodies /Badies brauchen direkten Zugriff auf die Spieler Objekte !
	friend class Item_BombUp;
	friend class Item_PowerUp;
	friend class Item_SpeedUp;
	friend class Item_EnableKick;
	friend class Item_Cocaine;
	friend class Item_Joint;
	friend class Item_Viagra;
	friend class Item_Condom;

private:
	bool m_bKickBomb; // Kann der Spieler Bomben schieben ?
	int m_iBombCount; // Die Anzahl der Bomben die der Spieler legen kann
	int m_iBombStrength; // Die St��rke der Bomben, die der Spieler legt, in Feldern
	int m_iSpeed; // Die momentane Geschwindigkeitsstufe des Spielers
	const char *m_cName;

	/*
	 * ALIVE		player is alive 
	 * FALLING		player is falling off the map
	 * DEADBYBOMB	player died by a bomb
	 * REALLYDEAD	player died by a bomb and got bombed again
	 */
	enum Status { ALIVE, FALLING, DEADBYBOMB, REALLYDEAD };
	Status m_iState;

	Vector3 m_vDisplacementModifier;
	float m_fOrientationCurrent; //the orientation is currently facing( used for rotation animation)
	float m_fRotationDegrees; //the amount of degrees the player has to rotate
	int m_iRotationDirection; // direction of rotation (-1 = neg, 1 = pos)

	int m_iID;
	int m_iPlacedBombID;

	int m_iPrimaryTexture; // index of base texture which should be mapped to the player
	int m_iSecondaryTexture; // index of second texture (happy face / sad face)

	bool m_bCanBomb; /*true if Player is allowed to place bomb 
						  manipulated by Item_Condom
						 */

	Map *m_pField;
	Item *m_pItem;
	ItemManager *m_pItemManager;

	Controller *m_pController;

	bool m_bDoSmoke;

	void move(); //moves the player
	void handleInput(); //checks the Input of the assigned controlelr
	void doDie(); //called when player got burned by a bomb

	void drawPlayer(); //draws the player object

	Timer m_tTimer; /*HACKISH:
							  timer is used to ensure that doesBurn() doesn't return true because of the same bomb, which killed the player
							*/

	//used to add smoke particles on a regular timestep
	int m_iTicks;

public:
	Player(int id, Map *pField, int Block, int zBlock);
	~Player();

	void attachController(Controller *pController);

	void placeBomb();

	void setStartPosition(int x, int z);

	void setPrimaryTexture(int skin);

	int getPrimaryTexture()
	{
		return m_iPrimaryTexture;
	};
	int getSecondaryTexture()
	{
		return m_iSecondaryTexture;
	};

	int getBombStrength();
	int getID()
	{
		return m_iID;
	};

	ItemManager *getItemManager()
	{
		return m_pItemManager;
	};
	void setName(const char *name);
	const char *getName()
	{
		return m_cName;
	};

	bool getKick()
	{
		return m_bKickBomb;
	};
	bool isDead();

	void update();
	// checks for collisions with other players
	void checkPlayerPlayerCollisions();

	void draw();
};

#endif
