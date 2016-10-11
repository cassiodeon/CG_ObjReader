#include "OBJReader.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_X WINDOW_WIDTH
#define MAX_Y WINDOW_HEIGHT

#define M_PI 3.14159265358979323846

OBJReader objReader;
Mesh* mesh;
map<string, Material*> materialLib;

double widthScreen = 800, heightScreen = 600;

GLdouble eyeX = 0, eyeY = 0, eyeZ = 0;
GLdouble directionX = 0.0, directionY = 0.0, directionZ = -1.0;
GLdouble angle = 270.0;
GLdouble zNear = 0.5, zFar = 100.0, fovy = 66;

GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_position[] = { 5.0, 25.0, 5.0, 0.0 };

//Variáveis para controle de configurações
bool iluminacao = true, textura = true;
GLdouble shadeModel = GL_SMOOTH;

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);  glVertex3f(2, 3, 3);

	for (int i = 0; i < mesh->groups.size(); i++)
	{
		Group* gr = mesh->groups[i];
		int quantidadeVert = 0;
		if (gr->draw) {
			Material* mat = materialLib[gr->nameMaterial];
			//glColor3f(1.0, 1.0, 1.0);
			if (mat != nullptr) {
				GLuint tid = mat->ID;
				//GLfloat mat_shininess[] = { 0.06 };
				glBindTexture(GL_TEXTURE_2D, tid);

				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat->ka);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->kd);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->ks);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &mat->ns);
			}

			for (int j = 0; j < gr->groupFace.size(); j++)
			{
				Face* f = gr->groupFace[j];
				if (f->vertex.size() == 3 && quantidadeVert != f->vertex.size()) {
					//glEnd();
					//glBegin(GL_TRIANGLES);
				}
				else if (f->vertex.size() == 4 && quantidadeVert != f->vertex.size()) {
					//glEnd();
					//glBegin(GL_QUADS);
				}
				else {
					//glEnd();
					//glBegin(GL_POLYGON);
				}
				glBegin(GL_POLYGON);
				for (int k = 0; k < f->vertex.size(); k++)
				{
					if (f->normals[k] > -1) {
						glNormal3fv(mesh->allNormals[f->normals[k]]->coord);
					}

					if (f->mappings[k] > -1) {
						TextureMapping* tm = mesh->allMappings[f->mappings[k]];
						glTexCoord2f(tm->texture[0], tm->texture[1]);

					}

					int indiceVertex = f->vertex[k];
					Vertex* v = mesh->allVertex[indiceVertex];
					glVertex3f(v->coord[0], v->coord[1], v->coord[2]);
				}
				glEnd();
			}
		}
		//glEnd();
	}

	glFlush();
}

void init(void)
{
	/* select clearing (background) color */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColor3f(1.0, 1.0, 1.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_FRONT);

	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(shadeModel);

	//Hbilita texturas
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Nome do arquivo obj
	objReader.path = "D:/Unisinos/CG_ObjReader/Imagens/";
	//Monta o objeto retornando a malha
	mesh = objReader.createOBJ("trout.obj");

	//Monta o map de materials
	materialLib = objReader.getMaterialLib(mesh->fileNameMaterial);

	GLuint* ids = new GLuint[materialLib.size()];
	glGenTextures(materialLib.size(), ids);
	int count = 0;
	map<string, Material*>::iterator it;
	for (it = materialLib.begin(); it != materialLib.end(); it++)
	{
		Material* mt = it->second;
		mt->ID = ids[count++];

		Image* img = mt->img;
		if (img != nullptr) {
			glBindTexture(GL_TEXTURE_2D, mt->ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());

			free(img->getPixels());
		}


	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	//GLfloat spot_exp[] = { 20.0 };
	//glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
}

void camera()
{
	// LOOKAT aqui
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, directionX, directionY, directionZ, 0, 3, 0);
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	widthScreen = width;
	heightScreen = height;
	gluPerspective(fovy, widthScreen / (float)heightScreen, zNear, zFar);
	camera();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case '+':
		eyeY = eyeY + 0.25;
		camera();
		break;
	case '-':
		eyeY = eyeY - 0.25;
		camera();
		break;
	case 't':
	case 'T':
		if (textura) {
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glEnable(GL_TEXTURE_2D);
		}
		textura = !textura;
		break;
	case 's':
	case 'S':
		if (shadeModel == GL_SMOOTH) {
			glShadeModel(GL_FLAT);
			shadeModel = GL_FLAT;
		}
		else {
			glShadeModel(GL_SMOOTH);
			shadeModel = GL_SMOOTH;
		}
		break;
	case 'l':
	case 'L':
		if (iluminacao) {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}else{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}
		iluminacao = !iluminacao;
		//cout << iluminacao;
		break;
	case 'Q':
	case 'q':
		cout << "Encerrando aplicacao..." << endl;
		exit(0);
		break;
	}

	cout << "Iluminacao = " + iluminacao;
	cout << (iluminacao ? "Ligado" : "Desligado");
	cout << "\n";
	cout << "Textura = ";
	cout << (textura ? "Ligado":"Desligado");
	cout << "\n";
	cout << "ShadeModel = ";
	cout << (shadeModel == GL_SMOOTH ? "GL_SMOOTH" : "GL_FLAT");
	cout << "\n";
	glutPostRedisplay();
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

void drawSimpleOBJ() {
	for (int i = 0; i < mesh->groups.size(); i++)
	{
		Group* gr = mesh->groups[i];
		int quantidadeVert = 0;
		glLoadName(i);
		//glPushName(i);
		for (int j = 0; j < gr->groupFace.size(); j++)
		{
			
			Face* f = gr->groupFace[j];
			if (f->vertex.size() == 3 && quantidadeVert != f->vertex.size()) {
				//glEnd();
				//glBegin(GL_TRIANGLES);
			}
			else if (f->vertex.size() == 4 && quantidadeVert != f->vertex.size()) {
				//glEnd();
				//glBegin(GL_QUADS);
			}
			else {
				//glEnd();
				//glBegin(GL_POLYGON);
			}
			glBegin(GL_POLYGON);
			for (int k = 0; k < f->vertex.size(); k++)
			{
				int indiceVertex = f->vertex[k];
				Vertex* v = mesh->allVertex[indiceVertex];
				glVertex3f(v->coord[0], v->coord[1], v->coord[2]);
			}
			glEnd();
		}
		//glEnd();
		//glPopName();
	}
	//glPopName();
}

void processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr;

	printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) { /*  for each hit  */
		names = *ptr;
		//printf(" number of names for this hit = %d\n", names);
		ptr++;
		ptr++;
		ptr++;
		//printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
		//printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;
		//printf("   names are ");
		for (j = 0; j < names; j++) { //  for each name 
			printf("%d ", *ptr);
			mesh->groups[*ptr]->draw = !mesh->groups[*ptr]->draw;
			cout << "Grupo " + mesh->groups[*ptr]->name + (mesh->groups[*ptr]->draw ? " adicionado":" removido")+ "\n";
			ptr++;
		}
		printf("\n");
	}
}

#define BUFSIZE 512
void mouse(int button, int state, int x, int y)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(BUFSIZE, selectBuf);
	(void)glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	/*  create 2x2 pixel picking region near cursor location      */
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),	2.0, 2.0, viewport);
	
	gluPerspective(fovy, widthScreen / (float)heightScreen, zNear, zFar);
	drawSimpleOBJ();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();

	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	glutCreateWindow("Trabalho GA - Cássio Deon");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecialKeys);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}