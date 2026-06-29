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

#ifndef MAPPREVIEW_H
#define MAPPREVIEW_H

#include "../Map/StMapEntry.h"
#include "../Engine/Vector3.h"
#include <list>

class MapPreview {
private:
	// the mapEntry, which should be displayed
	StMapEntry m_stMapEntry;

	struct stArrowField {
		int xPos;
		int zPos;
		int iDirection;
	};

	list<stArrowField> m_listCrateFields;
	list<stArrowField> m_listBlockFields;

	list<stArrowField> m_listPlainFields_Color0;
	list<stArrowField> m_listPlainFields_Color1;

	list<stArrowField> m_listArrowFields_Color0;
	list<stArrowField> m_listArrowFields_Color1;

	list<stArrowField> m_listHoleFields_Color0;
	list<stArrowField> m_listHoleFields_Color1;

	list<stArrowField> m_listRandomFields;

	void drawCrateFields();
	void drawBlockFields();
	void drawPlainFields();
	void drawArrowFields();
	void drawHoleFields();
	void drawRandomFields();

public:
	MapPreview();

	// Sets the maps, which should be previewed
	void setMap(StMapEntry entry);

	// draw  m_stMapEntry
	void draw();
};

#endif