#include "ApplicationController.h"
#include <Windows.h>
#include <GL\freeglut.h>
#include "matrix_transform.hpp"

#include "Floor.h"
#include "Camera.h"
#include "ParticleManager.h"

#include <sys/timeb.h>
#include <time.h>
#include <cstdio>

using namespace std;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4x4;

ApplicationController::ApplicationController(int argc, char* argv[])
: mWindowSize(786.0f, 1024.0f)
, m_CurrentMousePosition(0,0)
, m_TimeDelta(0.0)
, m_SimulationSpeed(1.0)
{
	m_ParticleState = showParticle;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize((int)mWindowSize.x, (int)mWindowSize.y);
	glutCreateWindow("Real Time Rendering Fluids");
	glewInit();


	float nearplane = 0.1f;
	float farplane = 20.0f;

	float degreeRadian = glm::radians(0.02f);
	m_RotationMatrix = mat4x4(	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, glm::cos(degreeRadian), -glm::sin(degreeRadian), 0.0f, 
								0.0f, glm::sin(degreeRadian), glm::cos(degreeRadian), 0.0f, 
								0.0f, 0.0f, 0.0f, 1.0f
								);
	
	m_Camera = new Camera(	vec3(0.0f, 0.0f, 7.0f), 
							vec3(0.0f, 0.0f, 0.0f), 
							vec3(0.0f, 1.0f, 0.0f)
						);
	
	m_ProjectionMatrix = new mat4x4();
	(*m_ProjectionMatrix) = glm::perspective(3.14f/4.0f, (float)mWindowSize.x/ (float)mWindowSize.y, nearplane, farplane);

	m_Floor = new Floor(m_ProjectionMatrix);

	m_ParticleManager = new ParticleManager(m_ProjectionMatrix);
}	

ApplicationController::~ApplicationController(void)
{
	m_ParticleManager->~ParticleManager();
	m_Floor->~Floor();
	m_Camera->~Camera();

	m_ProjectionMatrix->~mat4x4();
}

//method developed by Jeff Chastine
void ApplicationController::changeViewPort(int width, int height)
{
	glViewport(0, 0, width, height);
}

void ApplicationController::keyEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		m_ParticleState = showParticle;
		break;
	case '2':
		m_ParticleState = showQuad;
		break;
	case '3':
		m_ParticleState = showFluidLinear;
		break;
	case '4':
		m_ParticleState = showFluidExponential;
		break;
	case 'n':
		m_SimulationSpeed = 1.0;
		break;
	case 'f':
		m_SimulationSpeed = 1.5;
		break;
	case 's':
		m_SimulationSpeed = 0.2;
		break;
	case 'x':
		m_SimulationSpeed = 0.0;
		break;
	}
}

/*	button: 0 - linke Maustaste 
			1 - mittlere Maustaste
			2 - rechte Maustaste
			3 und 4 - scrollen
	state:	0 - drücken
			1 - loslassen
*/
void ApplicationController::mouseButtonEvent(int button, int state, int x, int y)
{
	/*std::printf("button: %i \n", button);
	std::printf("state: %i\n", state);*/
	
	if (button == 0)
	{
		if (state == 0)
		{
			m_CameraAction = Camera::action::rotate;
			m_CurrentMousePosition.x = x;
			m_CurrentMousePosition.y = y;
		} else
		{
			m_CameraAction = Camera::action::none;
			m_CurrentMousePosition.x = 0;
			m_CurrentMousePosition.y = 0;
		}
	} else if (button == 2)
	{
		if (state == 0)
		{
			m_CameraAction = Camera::action::translate;
			m_CurrentMousePosition.x = x;
			m_CurrentMousePosition.y = y;
		} else
		{
			m_CameraAction = Camera::action::none;
			m_CurrentMousePosition.x = 0;
			m_CurrentMousePosition.y = 0;
		}
	} else if (button == 3)
	{
		m_Camera->update(vec2(-ZOOM_FACTOR, 0.0f), Camera::action::zoom);
	} else if (button == 4)
	{
		m_Camera->update(vec2(ZOOM_FACTOR, 0.0f), Camera::action::zoom);
	}
}

//Funktion wird nur bei gedrückter Maustaste(beliebige Taste) ausgeführt
void ApplicationController::mouseMoveEvent(int x, int y)
{
	/*std::printf("x: %i\n", x);
	std::printf("y: %i\n", y);*/
	
	vec2 mouseMovement = m_CurrentMousePosition - vec2(x,y);
	m_Camera->update(mouseMovement, m_CameraAction);
	m_CurrentMousePosition.x = x;
	m_CurrentMousePosition.y = y;
}

void ApplicationController::idle()
{
	glutPostRedisplay();
}

void ApplicationController::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);

	const mat4x4* viewMatrix = m_Camera->getViewMatrix();

	m_Floor->draw(viewMatrix);

	m_ParticleManager->render(viewMatrix, m_ParticleState, mWindowSize);

	glutSwapBuffers();
}

void ApplicationController::update() {
	m_TimeDelta += getTimeDelta();
	
	if ( m_TimeDelta < MIN_TIME_DELTA ) return;

	m_Floor->update(&m_RotationMatrix);
	m_ParticleManager->update(m_TimeDelta*m_SimulationSpeed);
	m_TimeDelta = 0.0;

	render();
}

void ApplicationController::run() {
	glutMainLoop();
}

//method created by Christof Rezk-Salama
//Künstliche Intelligenz Übung 2 - Musterlösung
double ApplicationController::getTimeDelta() {

	__time64_t ltime;
	struct __timeb64 tstruct;

	static bool bFirstTime = true;
	static long nStartMilliSeconds;
	static long nMilliSeconds = 0;
	static long nStartCount   = 0;

	if (bFirstTime) {
		_time64( &ltime );
		nStartMilliSeconds = (unsigned long) ltime;
		nStartMilliSeconds *= 1000;
		_ftime64_s( &tstruct );
		nStartMilliSeconds += tstruct.millitm;        
		bFirstTime = false;
		nStartCount = nStartMilliSeconds;
	}

	_time64( &ltime );
	nMilliSeconds = (unsigned long) ltime;
	nMilliSeconds *= 1000;
	_ftime64_s( &tstruct );
	nMilliSeconds += tstruct.millitm;        
	bFirstTime = false;

	//nMilliSeconds -= nStartMilliSeconds;
	//printf( "Plus milliseconds:%u\n",nMilliSeconds-nStartCount);

	double deltaTime = double(nMilliSeconds-nStartCount)/1000.0;
	nStartCount = nMilliSeconds;

	if ( deltaTime < 0 )	return 0.0;

	return deltaTime;
}