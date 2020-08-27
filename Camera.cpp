#define _USE_MATH_DEFINES

#include "Camera.h"
#include "matrix_transform.hpp"
#include "rotate_vector.hpp"
#include "Math.h"
#include <math.h>
#include <cstdio>

Camera::Camera(vec3& position, vec3& lookAt, vec3& up)
	:m_Azimuth(0.0f), m_Elevation(0.0f), m_LookAtPosition(lookAt)
{
	
	vec3 zCam = -glm::normalize(lookAt - position);
	vec3 yCam = glm::normalize(up);
	vec3 xCam = glm::cross(yCam, zCam);
	yCam = glm::cross(zCam, xCam);

	//create camera coordinate system
	m_CameraCoords[3] = vec4(position, 1.0f);
	m_CameraCoords[2] = vec4(zCam, 0.0f);
	m_CameraCoords[1] = vec4(yCam, 0.0f);
	m_CameraCoords[0] = vec4(xCam, 0.0f);
	
	m_ViewMatrix = new mat4x4();
	(*m_ViewMatrix) = glm::inverse(m_CameraCoords);
}

Camera::~Camera(void)
{
}

const mat4x4* Camera::getViewMatrix()
{
	return m_ViewMatrix;
}

void Camera::update(const vec2& direction, action act)
{
	if (act == action::rotate) calcRotation(direction);
	if (act == action::translate) calcTranslation(direction);
	if (act == action::zoom) calcZoom(direction);

	calcViewMatrix();
}

/*	Azimuth:	300 pixel definieren eine Rotation um 180°
 *	Elevation:	300 pixel definieren eine Rotatoin um 90° beginnend vom Zentrum.
 */
void Camera::calcRotation(const vec2& direction)
{
	m_Azimuth += -(direction.x / 600.0f * M_PI);
	if (m_Azimuth < -M_PI) m_Azimuth = -M_PI;
	if (m_Azimuth > M_PI) m_Azimuth = M_PI;

	m_Elevation += -(direction.y / 1200.0f * M_PI);
	if (m_Elevation < -M_PI_2) m_Elevation = -M_PI_2;
	if (m_Elevation > M_PI_2) m_Elevation = M_PI_2;
}

// 100 Pixel repräsentieren eine Translation um 1
void Camera::calcTranslation(const vec2& direction)
{
	m_CameraCoords[3][0] += direction.x / 100.0f;
	m_CameraCoords[3][1] -= direction.y / 100.0f;
}

void Camera::calcZoom(const vec2& direction)
{
	vec3 dir = glm::normalize(m_CameraCoords[3]);
	dir *= direction.x;
	m_CameraCoords[3].x += dir.x;
	m_CameraCoords[3].y += dir.y;
	m_CameraCoords[3].z += dir.z;
}

/*	Immer zuerst um Azimuth rotieren, dann erst Elevation
	Alternativ muss die Rotation von Elevation in Azimuth mit einberechnet werden
*/	
void Camera::calcViewMatrix()
{
	mat4x4 aziRot;
	Math::createRotationMatrix(m_Azimuth, vec3(0,1,0), vec3(0,0,1), &aziRot);

	mat4x4 evaRot;
	//bestimme die Rotation der ElevationMatrix. Rotiert wird um die x-Achse des Kamerakoordinatensystems
	//Vor der Erstellung der Matrix muss die Kamera x-Achse aber erst in Weltkoordinaten transformiert werden
	Math::createRotationMatrix(m_Elevation, aziRot* m_CameraCoords[0], aziRot* m_CameraCoords[1], &evaRot);
	
	(*m_ViewMatrix) = glm::inverse(evaRot * aziRot * m_CameraCoords);
}