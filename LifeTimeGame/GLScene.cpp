#include "GLScene.h"


int size = 500;

Life* life3d = new Life(size / 5, size / 5, size / 5);

int window_width;
int window_height;
int Global_Window_Handle;
int g_ErrorCode;
float y_offset;
float x_offset;
float scal = 0.0f;

float rot_x = 0.1f;
float rot_y = 0.7f;
float rot_z = 0.3f;
float rot_angle = 0.1f;
bool Rotate_Stop = true;
bool Produce_Stop = true;
int time_e = clock();

#define  GLUT_WHEEL_UP 3           //定义滚轮操作
#define  GLUT_WHEEL_DOWN 4

void GLScene(int argc, char* argv[])
{
	//刚开始的默认的原始生命
	newlife3d();

	glutInit(&argc, argv);

	window_width = glutGet(GLUT_SCREEN_WIDTH);
	window_height = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition(window_width /8, window_height /8);
	glutInitWindowSize(window_width/1.5, window_height/1.5);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	Global_Window_Handle = glutCreateWindow("Game of Life");
	glutInitWindowSize(window_width, window_height);
	
	
	//主控部分
	glutDisplayFunc(DisplayGL);
	glutMouseFunc(MouseWheel);
	glutKeyboardFunc(KeyboardGL);
	glutReshapeFunc(ReshapeGL);
	//

	glClearColor(0.156f, 0.172f, 0.203f, 1.00f);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);

}

void Cleanup()
{
	if (Global_Window_Handle != 0)
	{
		glutDestroyWindow(Global_Window_Handle);
		Global_Window_Handle = 0;
	}
	if (false)
	{
		exit(g_ErrorCode);
	}

}

//初始化新的生命
void newlife3d()
{
	// ew--calling a destructor
	life3d->~Life();
	life3d = new Life(size / 5, size / 5, size / 5);
	for (int i = 0; i < int(0.04 * (size / 5) * (size / 5) * (size / 5)); i++)
	{
		int x = rand() % size / 5 + 1;
		int y = rand() % size / 5 + 1;
		int z = rand() % size / 5 + 1;
		life3d->setLife(x, y, z, 1);
	}
}

void DisplayGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//渲染函数
	render3d();
	glutSwapBuffers();
	glutPostRedisplay();
}

void MouseWheel(int button, int state, int x, int y)
{

	if (state == GLUT_UP && button == GLUT_WHEEL_UP)
	{
		scal += 1.0f;
	}

	if (state == GLUT_UP && button ==GLUT_WHEEL_DOWN)
	{
		scal -= 1.0f;
	}
}

void KeyboardGL(unsigned char c, int x, int y)
{
	if (c == ' ')
	{
		Produce_Stop = !Produce_Stop;
	}
	if (c == 'r')
	{
		Rotate_Stop = !Rotate_Stop;
	}
	if (c == 'w')
	{
		y_offset -= 0.1;
	}
	if (c == 's')
	{
		y_offset += 0.1;
	}
	if (c == 'd')
	{
		x_offset -= 0.1;
	}

	if (c == 'a')
	{
		x_offset += 0.1;
	}

	if (c == '1')
	{
		size = 200;
		newlife3d();
	}

	if (c == '2')
	{
		size = 300;
		newlife3d();
	}
	if (c == '3')
	{
		size = 400;
		newlife3d();
	}
	if (c == '4')
	{
		size = 600;
		newlife3d();
	}
	if (c == '5')
	{
		size = 800;
		newlife3d();
	}

}

void ReshapeGL(int w, int h)
{
	if (h == 0)										// Prevent A Divide By Zero error
	{
		h = 1;										// Making Height Equal One
	}

	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	// Setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)window_width / (GLdouble)window_height, 0.1, 100.0);

	//render();
	glutPostRedisplay();
}

void render3d()
{
	if (size <= 800)
	{
		float y_t = 0.0f;
		float x_t = 0.0f;
		float z_t = 0.0f;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// clear color and depth buffers 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glTranslatef(0.0f + x_offset, 0.0f + y_offset, -7.0f + scal);
		glRotatef(rot_angle / 3, rot_x, rot_y, rot_z);
		glRotatef(rot_angle / 3, rot_z, rot_y, rot_x);
		glRotatef(rot_angle / 3, rot_x, rot_z, rot_y);
		glTranslatef(-2.0f, -2.0f, -2.0f);

		glBegin(GL_QUADS);
		float sz = 2.0f * 10.0f / size;
		for (int i = 0; i < size / 10; i++)
		{
			y_t = 0.0f;
			for (int j = 0; j < size / 10; j++)
			{
				x_t = 0.0f;
				for (int k = 0; k < size / 10; k++)
				{
					if (life3d->getLifeform(k + 1, j + 1, i + 1) == 1)
					{
						//法向量方向
						glNormal3f(0.0F, 0.0F, 1.0F);
						glVertex3f(sz + x_t, sz + y_t, sz + z_t); 
						glVertex3f(-sz + x_t, sz + y_t, sz + z_t);
						glVertex3f(-sz + x_t, -sz + y_t, sz + z_t); 
						glVertex3f(sz + x_t, -sz + y_t, sz + z_t);

						glNormal3f(0.0F, 0.0F, -1.0F);
						glVertex3f(-sz + x_t, -sz + y_t, -sz + z_t); 
						glVertex3f(-sz + x_t, sz + y_t, -sz + z_t);
						glVertex3f(sz + x_t, sz + y_t, -sz + z_t); 
						glVertex3f(sz + x_t, -sz + y_t, -sz + z_t);

						glNormal3f(0.0F, 1.0F, 0.0F);
						glVertex3f(sz + x_t, sz + y_t, sz + z_t); 
						glVertex3f(sz + x_t, sz + y_t, -sz + z_t);
						glVertex3f(-sz + x_t, sz + y_t, -sz + z_t); 
						glVertex3f(-sz + x_t, sz + y_t, sz + z_t);

						glNormal3f(0.0F, -1.0F, 0.0F);
						glVertex3f(-sz + x_t, -sz + y_t, -sz + z_t); 
						glVertex3f(sz + x_t, -sz + y_t, -sz + z_t);
						glVertex3f(sz + x_t, -sz + y_t, sz + z_t); 
						glVertex3f(-sz + x_t, -sz + y_t, sz + z_t);

						glNormal3f(1.0F, 0.0F, 0.0F);
						glVertex3f(sz + x_t, sz + y_t, sz + z_t); 
						glVertex3f(sz + x_t, -sz + y_t, sz + z_t);
						glVertex3f(sz + x_t, -sz + y_t, -sz + z_t); 
						glVertex3f(sz + x_t, sz + y_t, -sz + z_t);

						glNormal3f(-1.0F, 0.0F, 0.0F);
						glVertex3f(-sz + x_t, -sz + y_t, -sz + z_t); 
						glVertex3f(-sz + x_t, -sz + y_t, sz + z_t);
						glVertex3f(-sz + x_t, sz + y_t, sz + z_t); 
						glVertex3f(-sz + x_t, sz + y_t, -sz + z_t);
					}
					x_t += sz * 2.0f;
				}
				y_t += sz * 2.0f;
			}
			z_t += sz * 2.0f;
		}
		glEnd();
		if (Produce_Stop == true)
		{
			//cout << clock() - time_e << endl;
			if ((int)(clock() - time_e) > 100)
			{
				time_e = clock();
				life3d->update();
			}
		}

		if (Rotate_Stop)
		{
			rot_angle++;
			rot_x = ((int)((rot_x + 1.0f) * 10.0f) % 10) / 10.0f;
			rot_y = ((int)((rot_y + 1.0f) * 10.0f) % 10) / 10.0f;
			rot_z = ((int)((rot_z + 1.0f) * 10.0f) % 10) / 10.0f;
		}
		glPopMatrix();
	}
}

