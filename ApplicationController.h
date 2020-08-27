#pragma once
#include "glm.hpp"
#include <GL\glew.h>
#include "Definitions.h"
#include "Camera.h"

class Floor;
class ParticleManager;

class ApplicationController
{
public:
	ApplicationController(int argc, char* argv[]);
	~ApplicationController(void);

	void				changeViewPort(int width, int height);
	void				keyEvent(unsigned char key,int x,int y);
	void				mouseButtonEvent(int button, int state,int x,int y);
	void				mouseMoveEvent(int x, int y);
	void				idle();

	void				update();
	void				render();
	void				run();

protected:
	double				getTimeDelta();

private:

	Floor*				m_Floor;
	Camera*				m_Camera;

	ParticleManager*	m_ParticleManager;
	ParticleStatus		m_ParticleState;

	glm::mat4x4*		m_ProjectionMatrix;
	glm::mat4x4			m_RotationMatrix;

	const glm::vec2		mWindowSize;

	glm::vec2			m_CurrentMousePosition;

	double				m_TimeDelta;
	double				m_SimulationSpeed;

	Camera::action		m_CameraAction;
};

