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

#ifndef MENUITEM_H
#define MENUITEM_H

#include <glm/glm.hpp>

class Menu;

class MenuItem {
protected:
	// the positon of the menuitem
	glm::vec3 m_vPosition;
	// the caption of this menuitem
	//	char * m_cCaption;
	char m_cCaption[50];
	// is this MenuItem active ?
	bool m_bActive;
	// does this menuItem handle input  ?
	bool m_bInteractive;
	// the current value of the MenuItem
	int m_iValue;

	// Tmp
	void drawQuad();

public:
	MenuItem(const char *caption);
	virtual ~MenuItem() {};
	//this function is called when this Menuitem is active
	void setActive(bool bActive);
	bool isInteractive()
	{
		return m_bInteractive;
	};

	//specifies the position of this MenuItem
	virtual void setPosition(glm::vec3 vPosition);
	glm::vec3 getPosition()
	{
		return m_vPosition;
	};

	// Virtual Functions for Input Handling
	virtual void enter() {};
	virtual void left() {};
	virtual void right() {};
	virtual void up() {};
	virtual void down() {};
	virtual void space() {};

	// sets / gets the current value of the Menuitem
	virtual int getValue();
	virtual void setValue(int value) {};

	// returns the width of this MenuItem
	//	virtual float getWidth(){};
	//	virtual float getHeight();

	virtual void draw() {};
};

#endif
