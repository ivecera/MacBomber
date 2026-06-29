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

#include <SDL3/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../Application.h"
#include "../Config.h"

Camera::Camera()
{
	Vector3 vPosition = Vector3(0.0, 0.0, 0.0);
	Vector3 vView = Vector3(0.0, 0.0, 10.0);
	Vector3 vUp = Vector3(0.0, 1.0, 0.0);

	m_vPosition = vPosition;
	m_vView = vView;
	m_vUp = vUp;

	//	m_stPresets[0].vPosition = Vector3(9.5,17,13);
	//	m_stPresets[0].vView = Vector3(9.5,3.65,8.7);

	m_stPresets[0].vPosition = Vector3(9.5, 17, 13);
	m_stPresets[0].vView = Vector3(9.5, 5, 9);
	m_stPresets[0].fFogStart = 20;
	m_stPresets[0].fFogEnd = 25;

	m_stPresets[1].vPosition = Vector3(9.53, 16.7, 17);
	m_stPresets[1].vView = Vector3(9.53, 4.58, 10);
	m_stPresets[1].fFogStart = 22;
	m_stPresets[1].fFogEnd = 26;

	m_stPresets[2].vPosition = Vector3(9.5, 17, 8.5);
	m_stPresets[2].vView = Vector3(9.5, 3.1, 7.6560);
	m_stPresets[2].fFogStart = 18;
	m_stPresets[2].fFogEnd = 25;

	m_iPreset = 0;
}
void Camera::positionCamera(float positionX, float positionY, float positionZ,
			    float viewX, float viewY, float viewZ,
			    float upVectorX, float upVectorY, float upVectorZ)
{
	Vector3 tmp_vPosition(positionX, positionY, positionZ);
	Vector3 tmp_vView(viewX, viewY, viewZ);
	Vector3 tmp_upVector(upVectorX, upVectorY, upVectorZ);

	m_vPosition = tmp_vPosition;
	m_vView = tmp_vView;
	m_vUp = tmp_upVector;
}

void Camera::moveCamera(float speed)
{
	/*
 	* Determine the direction we are looking at.
 	* This is done by subtracting the position vector from the view vector.
 	*/

	Vector3 vDirection = m_vView - m_vPosition;

	/*
	* We have calculated the direction vector we are looking at.
	* Now we move in that direction by multiplying the x,y,z values
	* of the direction vector with the corresponding elements of our
	* position vector.
	*
	*/

	m_vPosition.x += vDirection.x * speed * Application::m_fReciprocalFPS;
	m_vPosition.y += vDirection.y * speed * Application::m_fReciprocalFPS;
	m_vPosition.z += vDirection.z * speed * Application::m_fReciprocalFPS;

	/*
	 * Calculate a new viewpoint
	 */
	m_vView.x += vDirection.x * speed * Application::m_fReciprocalFPS;
	m_vView.y += vDirection.y * speed * Application::m_fReciprocalFPS;
	m_vView.z += vDirection.z * speed * Application::m_fReciprocalFPS;
}

void Camera::strafeCamera(float distance)
{
	// The movement direction is perpendicular to the up and view vectors
	Vector3 vStrafeAxis = crossProduct((m_vView - m_vPosition), m_vUp);

	vStrafeAxis = normalize(vStrafeAxis);

	m_vPosition.x +=
		vStrafeAxis.x * distance * Application::m_fReciprocalFPS;
	m_vPosition.z +=
		vStrafeAxis.z * distance * Application::m_fReciprocalFPS;

	m_vView.x += vStrafeAxis.x * distance * Application::m_fReciprocalFPS;
	m_vView.z += vStrafeAxis.z * distance * Application::m_fReciprocalFPS;
}

void Camera::rotateView(float angle, float x, float y, float z)
{
	Vector3 vNewView;

	//Get the view vector (The direction we are facing)
	Vector3 vView = m_vView - m_vPosition;

	// Calculate the sine and cosine of the angle once
	float cosTheta = SDL_cosf(angle);
	float sinTheta = SDL_sinf(angle);

	//Find the new x position for the new rotated point
	vNewView.x = (cosTheta + (1 - cosTheta) * x * x) * vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta) * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta) * vView.z;

	// Find the new y position for the new rotated point
	vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta) * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y) * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta) * vView.z;

	// Find the new z position for the new rotated point
	vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta) * vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta) * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z) * vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
}

void Camera::setViewByMouse()
{
	float screenMiddleX = Application::screenWidth * 0.5f;
	float screenMiddleY = Application::screenHeight * 0.5f;

	// Store the current mouse coordinates obtained via SDL_GetMouseState(&mouseX,&mouseY)
	float mouseX;
	float mouseY;

	float angleY; // The angle by which the viewpoint should be rotated around the Y axis
	float angleZ; // The angle by which the viewpoint should be rotated around the Z axis

	// Where is the mouse currently?
	SDL_GetMouseState(&mouseX, &mouseY);

	// If no mouse movement occurred - abort
	if (mouseX == screenMiddleX && mouseY == screenMiddleY)
		return;

	// Move the mouse back to the screen center
	SDL_WarpMouseInWindow(Application::m_pWindow, screenMiddleX,
			      screenMiddleY);

	/* Calculate how much the mouse has moved in the x and y directions.
	 * By dividing we convert these values into actual angles.
	 */
	angleY = (screenMiddleX - mouseX) / 1000.0f;
	angleZ = (screenMiddleY - mouseY) / 1000.0f;

	/* The axis around which the viewpoint should be rotated horizontally.
	 * This is perpendicular to the view and up vectors, so we calculate
	 * the cross product of both vectors.
	 */
	Vector3 vAxis = crossProduct((m_vView - m_vPosition), m_vUp);

	// Normalize the resulting vector to unit length (1)
	vAxis = normalize(vAxis);

	rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	rotateView(angleY, 0, 1, 0);
}

void Camera::setView()
{
	glm::mat4 v = glm::lookAt(glm::vec3(m_vPosition.x, m_vPosition.y,
					    m_vPosition.z),
				  glm::vec3(m_vView.x, m_vView.y, m_vView.z),
				  glm::vec3(m_vUp.x, m_vUp.y, m_vUp.z));
	glMultMatrixf(glm::value_ptr(v));
}

void Camera::setPreset(int nr)
{
	m_iPreset = nr;
	m_vView = m_stPresets[nr].vView;
	m_vPosition = m_stPresets[nr].vPosition;

	glFogf(GL_FOG_START, m_stPresets[nr].fFogStart);
	glFogf(GL_FOG_END, m_stPresets[nr].fFogEnd);
}
