
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

#include <GLUT/glut.h>
#include <string>
#include <iostream>
using namespace std;

#include "TextDrawer.h"
#include "FTGL/FTGLTextureFont.h"
#include "FTGLPolygonFont.h"

#include "Defines.h"
#include "Application.h"
#include "TextureManager.h"
#include "ortho.h"

#include "../Config.h"

TextDrawer::TextDrawer()
{
	m_iWidth = Application::screenWidth;
	m_iHeight = Application::screenHeight;

	string fontfile = Application::m_strResourcePath;
	fontfile = fontfile + "/Fonts/annifont.ttf";

	// fix for a nasty 10.4.7 ATI X1600 glTexSubImage2D() bug *deprecated*
	std::string renderer = (const char *)glGetString(GL_RENDERER);
	std::string version = (const char *)glGetString(GL_VERSION);

	if (renderer == std::string("ATI Radeon X1600 OpenGL Engine") &&
	    version == std::string("1.5 ATI-1.4.32")) {
		m_ttfSmallFont = new FTGLPolygonFont(fontfile.c_str());
		m_ttfStdFont = new FTGLPolygonFont(fontfile.c_str());
		m_ttfBigFont = new FTGLPolygonFont(fontfile.c_str());
		cout << "TextDrawer: Using low quality font to avoid crash (ATI Driver bug in Mac OS 10.4.7) !"
		     << endl;
	} else {
		m_ttfSmallFont = new FTGLTextureFont(fontfile.c_str());
		m_ttfStdFont = new FTGLTextureFont(fontfile.c_str());
		m_ttfBigFont = new FTGLTextureFont(fontfile.c_str());
	}

	m_ttfSmallFont->FaceSize(14);
	m_ttfStdFont->FaceSize(18);
	m_ttfBigFont->FaceSize(50);

	m_pCurrentFont = m_ttfStdFont;
}

TextDrawer::~TextDrawer()
{
	delete m_ttfSmallFont;
	delete m_ttfStdFont;
	delete m_ttfBigFont;
}

void TextDrawer::setSize(int size)
{
	switch (size) {
	case SMALL:
		m_pCurrentFont = m_ttfSmallFont;
		break;
	case STD:
		m_pCurrentFont = m_ttfStdFont;
		break;
	case BIG:
		m_pCurrentFont = m_ttfBigFont;
		break;
	default:
		m_pCurrentFont = m_ttfStdFont;
	}
}

void TextDrawer::drawText(float xPos, float yPos, const char *pText,
			  float fScale)
{
	glPushMatrix();
	glTranslatef(relToAbs(xPos, 0), relToAbs(yPos, 1), 0);
	glScalef(fScale, fScale, fScale);
	m_pCurrentFont->Render(pText);
	glPopMatrix();
}

void TextDrawer::drawTextCentered(float xPos, float yPos, const char *pText,
				  float fScale)
{
	float height;
	float width;
	float llx, lly, llz, urx, ury, urz;

	// get Font Bounding Box
	m_pCurrentFont->BBox(pText, llx, lly, llz, urx, ury, urz);

	// Calculate the length & width of the bbox
	width = urx - llx;
	height = ury - lly;

	// Correct position and draw Text
	glPushMatrix();
	glTranslatef(relToAbs(xPos, 0) - ((width / 2) * fScale),
		     relToAbs(yPos, 1), 0.0);
	glScalef(fScale, fScale, fScale);
	m_pCurrentFont->Render(pText);
	glPopMatrix();
}

float TextDrawer::getLength(const char *pText)
{
	//	float llx, lly, llz, urx, ury, urz;
	return absToRel(m_pCurrentFont->Advance(pText), 0);
	//	m_pCurrentFont->BBox(pText,llx,lly,llz,urx,ury,urz);
}
