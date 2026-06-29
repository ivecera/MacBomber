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

#ifndef CCAMERA
#define CCAMERA

#include <glm/glm.hpp>
#include <SDL3/SDL.h>

/** This class represents the virtual camera in the 3D world
  *
  *
  */

struct stPreset {
	// Cameras position
	glm::vec3 vPosition;

	// the coordinate the camera is looking at
	glm::vec3 vView;
	// since we have changing views (&use OpenGL fog) we store for each preset fog start/end values seperately
	float fFogStart = 0;
	float fFogEnd = 0;
};

class Camera {
private:
	// Predefined values for camera settings
	stPreset m_stPresets[3];

	//index of our currently uses preset
	int m_iPreset;

public:
	glm::vec3 m_vPosition; // The position of the virtual camera
	glm::vec3 m_vView; // The viewing direction of the virtual camera
	glm::vec3 m_vUp; // The direction that defines "up"
	// FIXME: Left vector

	Camera();

	/** Position the camera in the virtual world
		 * \param positionX,positionY,positionZ The camera's position in the world
		 * \param viewX,viewY,viewZ The vector the camera is looking at
		 * \param upVectorX,upVectorY,upVectorZ The vector describing which direction is "up"
		 */

	void positionCamera(float positionX, float positionY, float positionZ,
			    float viewX, float viewY, float viewZ,
			    float upVectorX, float upVectorY, float upVectorZ);

	/** Moves the camera through the virtual world forward and backward
		 *
		 * \param distance The amount by which the camera should be moved
		 *
		 */

	void
	moveCamera(float distance); // Moves the camera by the amount "distance"

	/** Strafe the camera by the amount distance to the left or right
		 *  \param distance The amount by which the camera should be strafed
		 *
		 */
	void strafeCamera(float distance);

	/** Rotate the camera around the axis (x,y,z)
		 *
		 * \param angle The angle by which to rotate
		 * \param x,y,z Define the axis around which to rotate
		 *
		 */
	void rotateView(float angle, float x, float y, float z);

	void setViewByMouse();
	void setView();

	void setPreset(int nr);
	int getPreset()
	{
		return m_iPreset;
	};
};

#endif