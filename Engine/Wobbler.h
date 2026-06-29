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

#ifndef WOBBLER_H
#define WOBBLER_H

class Wobbler {
private:
	// for each axis one Angle (in Radiants) - these are used to calculate the sin values
	float m_fRadX;
	float m_fRadY;
	float m_fRadZ;

	// the scalevalues should wobble around these values.
	float m_fMedianX;
	float m_fMedianY;
	float m_fMedianZ;

	// the maximum amount of wobbling around the median on each axis (in positive and negative direction)
	float m_fMaxX;
	float m_fMaxY;
	float m_fMaxZ;

	// the speed with which the m_fRad angles are incremented
	float m_fRadSpeedX;
	float m_fRadSpeedY;
	float m_fRadSpeedZ;

	// the calculated scale Values for each axis
	float m_fScaleValueX;
	float m_fScaleValueY;
	float m_fScaleValueZ;

	float doScale(float &rads, float median, float max);

public:
	// initRandom is true if start valus should be initiated randomly
	Wobbler();
	void update();

	float getScaleValueX()
	{
		return m_fScaleValueX;
	};
	float getScaleValueY()
	{
		return m_fScaleValueY;
	};
	float getScaleValueZ()
	{
		return m_fScaleValueZ;
	};

	void setRads(float radX, float radY, float radZ);
	void setRadSpeeds(float radX, float radY, float radZ);
	void setMedians(float medianX, float medianY, float medianZ);
	void setMaxima(float maxX, float maxY, float maxZ);
};

#endif
