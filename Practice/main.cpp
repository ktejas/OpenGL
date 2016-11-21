#include "GL\freeglut.h"

void RenderSceneSB()
{
	glutSwapBuffers();
}

void InitializeGlutCallbacks()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(RenderSceneSB);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Practice 01");

	InitializeGlutCallbacks();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glutMainLoop();

	return 0;
}