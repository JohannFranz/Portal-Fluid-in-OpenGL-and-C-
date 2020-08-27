#include "ApplicationController.h"
#include <GL\freeglut.h>

//callback methods created by Christof Rezk-Salama
//Künstliche Intelligenz Übung 2 - Musterlösung
ApplicationController* app = 0;
void display(void)                              { app->update();}
void reshape(int width, int height)             { app->changeViewPort(width, height);}
void keyboard(unsigned char key, int x, int y)  { app->keyEvent(key,x,y);}
void mouse(int button, int state, int x, int y) { app->mouseButtonEvent(button, state,x,y);}
void move(int x, int y)                         { app->mouseMoveEvent(x,y);}
void idle(void)                                 { app->idle();}
//void update(int value)							{ app->update();}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	app = new ApplicationController(argc, argv);
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutIdleFunc(idle);
	//glutTimerFunc(20, update, 0);

	app->run();

	return 0;
}





