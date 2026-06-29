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

#ifndef TOGGLEITEM_H
#define TOGGLEITEM_H

#include "MenuItem.h"
#include <vector>

struct stOption {
	// Name of the option e.g "Yes"
	//	char * name;
	char name[30];
	// Integer Value of the Option e.g "1"
	int value;
};

class ToggleItem : public MenuItem {
protected:
	// An STL Vector with Option(names) (...overkil, i know)
	vector<stOption> m_lOptionNames;
	// An iterator to the currently active Option
	vector<stOption>::iterator m_itIterator;

	void increaseValue();
	void decreaseValue();

public:
	ToggleItem(const char *caption);

	// Add an Option called "optionName" with integer Value "value"
	void addOption(const char *optionName, int value);
	void left();
	void right();
	void enter();

	void setValue(int value);
	//	float getWidth();
	virtual void draw();
};

#endif
