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

#include "../Application.h"
#include "ValueItem.h"
#include <SDL3/SDL_opengl.h>
#include "../Engine/TextDrawer.h"
#include "../Engine/intToString.h"
#include "../Engine/ortho.h"

#include <string>

ValueItem::ValueItem(const char *caption, int min, int max, int stepping)
	: MenuItem(caption)
{
	m_iMin = min;
	m_iMax = max;
	m_iStepping = stepping;

	m_iValue = m_iMin;
	m_strValue = convertValueToString(m_iValue);
}

void ValueItem::left()
{
	m_iValue -= m_iStepping;
	if (m_iValue < m_iMin)
		m_iValue = m_iMax;

	m_strValue = convertValueToString(m_iValue);
}

void ValueItem::right()
{
	m_iValue += m_iStepping;
	if (m_iValue > m_iMax)
		m_iValue = m_iMin;

	m_strValue = convertValueToString(m_iValue);
}

void ValueItem::setValue(int value)
{
	// FIXME: Needs check if value%m_iStepping is 0!!
	m_iValue = value;

	// check for boundries
	if (m_iValue > m_iMax)
		m_iValue = m_iMax;

	if (m_iValue < m_iMin)
		m_iValue = m_iMin;

	m_strValue = convertValueToString(m_iValue);
}
/*
float ValueItem::getWidth()
{
	float width = 0;
	width += 0.375;
	width += Application::m_pTextDrawer->getLength(m_strValue.c_str());
	return width;
	
}
*/
void ValueItem::draw()
{
	if (m_bActive) {
		drawQuad();
		//		glColor3f(1,0,0);
	}
	//	else
	//		glColor3f(1,1,1);

	Application::m_pTextDrawer->drawText(m_vPosition.x, m_vPosition.y,
					     m_cCaption);
	Application::m_pTextDrawer->drawText(m_vPosition.x + 0.375,
					     m_vPosition.y, m_strValue.c_str());

	//	glColor3f(1,1,1);
}
