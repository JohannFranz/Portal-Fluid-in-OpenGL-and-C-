#pragma once
#include "glm.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4x4;

class Camera
{
public:

	enum action
	{
		none,
		rotate,
		translate,
		zoom,
		countActions
	};

					Camera(vec3& position, vec3& lookAt, vec3& up);
					~Camera(void);

	const mat4x4*	getViewMatrix();
	
	void			update(const vec2& direction, action act);

private:
	void			calcViewMatrix();
	void			calcRotation(const vec2& direction);
	void			calcTranslation(const vec2& direction);
	void			calcZoom(const vec2& direction);

	mat4x4			m_CameraCoords;
	mat4x4*			m_ViewMatrix;
	vec3			m_LookAtPosition;

	float			m_Azimuth;		//rotation in radians
	float			m_Elevation;	//rotation in radians
};

