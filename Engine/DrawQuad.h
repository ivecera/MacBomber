#ifndef DRAWQUAD_H
#define DRAWQUAD_H

#include <SDL3/SDL_opengl.h>

inline void drawUnitQuad()
{
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
}

#endif
