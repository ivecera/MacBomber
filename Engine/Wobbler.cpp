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
#include "Wobbler.h"

Wobbler::Wobbler()
{
	m_fRadX = 0;
	m_fRadY = 0;
	m_fRadZ = 0;

	m_fMaxX = 0.1;
	m_fMaxY = 0.25;
	m_fMaxZ = 0.1;

	m_fMedianX = 1;
	m_fMedianY = 1;
	m_fMedianZ = 1;

	m_fRadSpeedX = 5;
	m_fRadSpeedY = 5;
	m_fRadSpeedZ = 5;
}

float Wobbler::doScale(float &rads, float median, float max)
{
	//	float sinus = sin(rads);
	//	float scaleValue = median + (sin(rads)  * (1-median)  );

	float scaleValue = median + (SDL_sinf(rads) * max);

	if (rads > 2 * SDL_PI_F)
		rads = 0;

	return scaleValue;
}

void Wobbler::update()
{
	// increase the rad angles with speed m_fRadSpeed
	m_fRadX += m_fRadSpeedX * Application::m_fReciprocalFPS;
	m_fRadY += m_fRadSpeedY * Application::m_fReciprocalFPS;
	m_fRadZ += m_fRadSpeedZ * Application::m_fReciprocalFPS;

	// calculate the new scaleVales
	m_fScaleValueX = doScale(m_fRadX, m_fMedianX, m_fMaxX);
	m_fScaleValueY = doScale(m_fRadY, m_fMedianY, m_fMaxY);
	m_fScaleValueZ = doScale(m_fRadZ, m_fMedianZ, m_fMaxZ);
}

void Wobbler::setRads(float radX, float radY, float radZ)
{
	m_fRadX = radX;
	m_fRadY = radY;
	m_fRadZ = radZ;
}
void Wobbler::setRadSpeeds(float radX, float radY, float radZ)
{
	m_fRadSpeedX = radX;
	m_fRadSpeedY = radY;
	m_fRadSpeedZ = radZ;
}

void Wobbler::setMedians(float medianX, float medianY, float medianZ)
{
	m_fMedianX = medianX;
	m_fMedianY = medianY;
	m_fMedianZ = medianZ;
}

void Wobbler::setMaxima(float maxX, float maxY, float maxZ)
{
	m_fMaxX = maxX;
	m_fMaxY = maxY;
	m_fMaxZ = maxZ;
}
