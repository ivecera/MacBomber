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

#ifndef TEXTDRAWER_H
#define TEXTDRAWER_H

class FTFont;

class TextDrawer {
private:
	int m_iWidth;
	int m_iHeight;
	//	FTGLPixmapFont * m_ttfStdFont;
	//	FTGLTextureFont * m_ttfStdFont;
	//	FTGLTextureFont * m_ttfBigFont;

	FTFont *m_ttfSmallFont;
	FTFont *m_ttfStdFont;
	FTFont *m_ttfBigFont;

	// pointer to the currently used font
	//	FTGLTextureFont * m_pCurrentFont;
	FTFont *m_pCurrentFont;

public:
	TextDrawer();
	~TextDrawer();
	void setSize(int size);
	void drawText(float xPos, float yPos, const char *pText,
		      float fScale = 1);
	void drawTextCentered(float xPos, float yPos, const char *pText,
			      float fScale = 1);

	// returns lenght of pText written in current Size
	float getLength(const char *pText);
};

#endif