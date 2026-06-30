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

#include "../Engine/MatrixStack.h"
#include "LevelScrollListItem.h"
#include "../Application.h"
#include "../Defines.h"
#include "../Map/MapManager.h"
#include "../Engine/TextureManager.h"
#include "../Map/StMapEntry.h"
#include "../Engine/TextDrawer.h"
#include "../Engine/ortho.h"
#include "../Engine/intToString.h"

LevelScrollListItem::LevelScrollListItem()
	: MenuItem("")
{
	m_iCurrentSlot = 0;
	m_iSlotsPerPage = 10;
	m_iOffset = 0;
	m_iSlotCount = Application::m_pMapManager->getMapCount();
}

void LevelScrollListItem::drawTriangle()
{
	/*
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLES);
		glVertex3f(10,0,0);
		glVertex3f(-10,10,0);
		glVertex3f(-10,-10,0);
	glEnd();
	 */
	float blah[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, blah);
	glColor3f(1.0f, 0.58f, 0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	Application::m_pTextureManager->bindTexture(MENU_ARROW_TEXTURE);
	//modelview.translate(m_vPosition.x-40,m_vPosition.y, m_vPosition.z);
	//		glNormal3f(0,0,1);
	modelview.apply();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(20, 20, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-20, 20, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-20, -20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(20, -20, 0);
	glEnd();
	glColor3f(1.0f, 1.0, 1.0f);

	glDisable(GL_BLEND);
}

void LevelScrollListItem::drawSlots()
{
	float yPos = m_vPosition.y;
	float slotSpacing = 0.05;
	StMapEntry tmp;

	float blah[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, blah);

	for (int i = 0; i < m_iSlotsPerPage; i++) {
		tmp = Application::m_pMapManager->getMap(m_iOffset + i);

		modelview.push();
		modelview.translate(relToAbs(0.031, 0),
				    relToAbs(yPos + 0.013, 1), 0);
		modelview.apply();

		// Draw an arrow to mark the currently selected Slot
		if ((i == m_iCurrentSlot) && (m_bActive))
			// which item is active
			drawTriangle();

		modelview.pop();

		(tmp.enabled) ? glColor3f(0, 1, 0) : glColor3f(1, 0, 0);

		Application::m_pTextDrawer->setSize(STD);
		Application::m_pTextDrawer->drawText(0.0625, yPos, tmp.name);
		yPos -= slotSpacing;
	}

	//	glColor3f(0,0,0);
}

void LevelScrollListItem::drawCount()
{
	int enabledMapCount = Application::m_pMapManager->getEnabledMapCount();
	float m_iXOffset = 0.0625;
	float yPos = 0.20;
	string text = convertValueToString(enabledMapCount);
	float length = Application::m_pTextDrawer->getLength(text.c_str());

	glColor3f(1, 1, 1);
	Application::m_pTextDrawer->drawText(m_iXOffset, yPos, text.c_str(),
					     0.8);
	Application::m_pTextDrawer->drawText(m_iXOffset += length + 0.006, yPos,
					     "of", 0.8);

	text = convertValueToString(m_iSlotCount);
	length = Application::m_pTextDrawer->getLength("of");
	Application::m_pTextDrawer->drawText(m_iXOffset += length + 0.006, yPos,
					     text.c_str(), 0.8);
	length = Application::m_pTextDrawer->getLength(text.c_str());
	Application::m_pTextDrawer->drawText(m_iXOffset += length + 0.0125,
					     yPos, "Maps selected.", 0.8);

	/*if (enabledMapCount <= 0)
		Application::m_pTextDrawer->drawText(25,80,"Please enable at least one map!.");*/
}

void LevelScrollListItem::up()
{
	if ((m_iCurrentSlot + m_iOffset) <
	    Application::m_pMapManager->getMapCount() - 1) {
		if (m_iCurrentSlot == m_iSlotsPerPage - 1)
			m_iOffset += 1;
		else
			m_iCurrentSlot++;
	}

	m_iValue = m_iCurrentSlot + m_iOffset;
}

void LevelScrollListItem::down()
{
	if (m_iCurrentSlot == 0) {
		if (m_iOffset > 0)
			m_iOffset -= 1;
	} else
		m_iCurrentSlot--;

	m_iValue = m_iCurrentSlot + m_iOffset;
}

void LevelScrollListItem::space()
{
	Application::m_pMapManager->toggleMap(m_iCurrentSlot + m_iOffset);
}

void LevelScrollListItem::draw()
{
	//glDisable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//		modelview.translate(m_vPosition.x ,m_vPosition.y, m_vPosition.z);
	drawSlots();
	drawCount();
	//	glEnable(GL_COLOR_MATERIAL);
}
