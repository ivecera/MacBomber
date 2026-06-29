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

#include "Application.h"
#include "ToggleItem.h"
#include <GLUT/glut.h>
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"

ToggleItem::ToggleItem(const char *caption)
	: MenuItem(caption)
{
}

void ToggleItem::increaseValue()
{
	m_itIterator++;
	// did we reach the end of the Optionlist ?
	if (m_itIterator == m_lOptionNames.end())
		// jump back to the beginning
		m_itIterator = m_lOptionNames.begin();

	//store the current Value
	m_iValue = (*m_itIterator).value;
}

void ToggleItem::decreaseValue()
{
	// did we reach the beginning of the Optionlist ?
	if (m_itIterator == m_lOptionNames.begin()) {
		// jump back to the end
		m_itIterator = m_lOptionNames.end();
		// go one step back ( *m_lOptionNames.end() is NULL)
		m_itIterator--;
	} else
		m_itIterator--;

	//store the current Value
	m_iValue = (*m_itIterator).value;
}

void ToggleItem::addOption(const char *optionName, int value)
{
	//create an Option with Name "optionName" and value "value"
	stOption option;
	//	option.name = optionName;
	strcpy(option.name, optionName);

	option.value = value;

	//put it into the optionlist
	m_lOptionNames.push_back(option);
	m_itIterator = m_lOptionNames.begin();

	// only needed for the first time we put something in there
	m_iValue = (*m_itIterator).value;
}

void ToggleItem::right()
{
	increaseValue();
}

void ToggleItem::left()
{
	decreaseValue();
}
void ToggleItem::enter()
{
	increaseValue();
}

void ToggleItem::setValue(int value)
{
	//loop through all Options and compare with the given Value
	vector<stOption>::iterator it;
	for (it = m_lOptionNames.begin(); it != m_lOptionNames.end(); it++) {
		// We have found an Option with the specified value
		if ((*it).value == value) {
			//make it our Currently selected Item & modify m_iValue accordingly
			m_iValue = value;
			m_itIterator = it;
		}
	}
}
/*
float ToggleItem::getWidth()
{
	float width = 0;
	width += 0.375;
	width += Application::m_pTextDrawer->getLength((*m_itIterator).name);
	return width;
}*/

void ToggleItem::draw()
{
	if (m_bActive) {
		drawQuad();
		//	glColor3f(1,0,0);
	}
	//else
	//	glColor3f(1,1,1);
	Application::m_pTextDrawer->drawText(m_vPosition.x, m_vPosition.y,
					     m_cCaption);
	Application::m_pTextDrawer->drawText(
		m_vPosition.x + 0.375, m_vPosition.y, (*m_itIterator).name);

	//glColor3f(1,1,1);
}
