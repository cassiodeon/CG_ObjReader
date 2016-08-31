#include <Windows.h>
#include <GL/glut.h>
#include "OBJReader.h"

OBJReader objReader;
Mesh* mesh;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	
	//Nome do arquivo obj
	objReader.pathFile = "D:/Unisinos/CG_ObjReader/Imagens/trout.obj";
	//Monta o objeto retornando a malha
	mesh = objReader.createOBJ();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cubo");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}