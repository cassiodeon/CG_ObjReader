#include <Windows.h>
#include <GL/glut.h>
#include "OBJReader.h"
#include <map>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_X WINDOW_WIDTH
#define MAX_Y WINDOW_HEIGHT

#define M_PI 3.14159265358979323846

OBJReader objReader;
Mesh* mesh;
map<char*, Material*> materialLib;


GLdouble eyeX = 0, eyeY = 0, eyeZ = 0;
GLdouble directionX = 0.0, directionY = 0.0, directionZ = -1.0;
GLdouble angle = 270.0;

void display(void)
{

#pragma region Monta Chão
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	// Vermelho
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -0.2, 0.0);
	glVertex3f(0.0, -0.2, 5.0);
	glVertex3f(-5.0, -0.2, 5.0);
	glVertex3f(-5.0, -0.2, 0.0);
	glEnd();

	// Verde
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -0.2, 0.0);
	glVertex3f(0.0, -0.2, 5.0);
	glVertex3f(5.0, -0.2, 5.0);
	glVertex3f(5.0, -0.2, 0.0);
	glEnd();

	// Amarelo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, -0.2, 0.0);
	glVertex3f(0.0, -0.2, -5.0);
	glVertex3f(5.0, -0.2, -5.0);
	glVertex3f(5.0, -0.2, 0.0);
	glEnd();

	// Azul
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, -0.2, 0.0);
	glVertex3f(0.0, -0.2, -5.0);
	glVertex3f(-5.0, -0.2, -5.0);
	glVertex3f(-5.0, -0.2, 0.0);
	glEnd();
#pragma endregion 

	for (int i = 0; i < mesh->groups.size(); i++)
	{
		Group* gr = mesh->groups[i];
		for (int j = 0; j < gr->groupFace.size(); j++)
		{
			Face* f = gr->groupFace[j];
			glBegin(GL_POLYGON);
			glColor3f(1.0, 1.0, 1.0);
			for (int k = 0; k < f->vertex.size(); k++)
			{
				int indiceVertex = f->vertex[k];

				float coords[3];
				coords[0] = mesh->allVertex[indiceVertex]->coord[0];
				coords[1] = mesh->allVertex[indiceVertex]->coord[1];
				coords[2] = mesh->allVertex[indiceVertex]->coord[2];
				//glTexCoord2f()
				glVertex3f(coords[0], coords[1], coords[2]);
			}
			glEnd();
		}
	}

	glFlush();
}

void init(void)
{
	/* select clearing (background) color */
	glClearColor(0, 0, 0, 0);

	//Nome do arquivo obj
	objReader.path = "C:/Workspace/Unisinos/ComputacaoGrafica/CG_ObjReader/Imagens/";
	//Monta o objeto retornando a malha
	mesh = objReader.createOBJ("trout.obj");
	materialLib = objReader.getMaterialLib(mesh->fileNameMaterial);

}

void camera()
{
	// LOOKAT aqui
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, directionX, directionY, directionZ, 0, 1, 0);
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(66, width / (float)height, 0.1, 10.0);
	camera();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Q':
	case 'q':
		cout << "Encerrando aplicacao..." << endl;
		exit(0);
		break;
	}
}

void rotacionaCamera(GLdouble incAngle)
{
	angle += incAngle;
	GLdouble newAngle = angle / 180 * M_PI;

	GLdouble ddx = cos(newAngle);
	GLdouble ddz = sin(newAngle);
	// eye em qualquer posição:
	directionX = eyeX + ddx;
	directionZ = eyeZ + ddz;

	camera();
}

void deslocaCamera(GLdouble desloc)
{
	GLdouble newAngle = angle / 180 * M_PI;

	GLdouble ddx = cos(newAngle);
	GLdouble ddz = sin(newAngle);

	eyeX += ddx * desloc;
	eyeZ += ddz * desloc;

	directionX = eyeX + ddx;
	directionZ = eyeZ + ddz;

	camera();
}

void keyboardSpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		rotacionaCamera(5);
	}
	else if (key == GLUT_KEY_LEFT)
	{
		rotacionaCamera(-5);
	}
	else if (key == GLUT_KEY_UP)
	{
		deslocaCamera(0.5);
	}
	else if (key == GLUT_KEY_DOWN)
	{
		deslocaCamera(-0.5);
	}

	glutPostRedisplay();
}

void mouse(int botao, int estado, int x, int y)
{
	if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
	}

	if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
	{
		glutPostRedisplay();
	}
	//camera();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	glutCreateWindow("ObjReader");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecialKeys);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}