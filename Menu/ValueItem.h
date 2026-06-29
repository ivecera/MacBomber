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

#ifndef VALUEITEM_H
#define VALUEITEM_H

#include "MenuItem.h"
#include <string>

class ValueItem : public MenuItem {
private:
	//Minimum & Maxmimum Value of the value
	int m_iMin;
	int m_iMax;
	int m_iStepping; //amount of increase / decrease of value

	string m_strValue; //m_iValue as string
	//converts m_iValue integer to a string

public:
	ValueItem(char *caption, int min, int max, int stepping);

	void enter() {};
	void left();
	void right();

	void setValue(int value);
	//	float getWidth();
	void draw();
};
#endif