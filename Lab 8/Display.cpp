#include <cstdlib>
#include "GLFW/glut.h"
#include "GLFW/glfw3.h"
#include "Cube.h"
#include "Display.h"
#include "Rename.h"

/*/
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D       // this marco is not defined in some implementations, so define it manually here
#endif
*/

namespace RubiksCube
{
	const double sticker_size = 0.83;
	const double block_size = 0.962;
	const double pivot_size = 2.1;
	Animation ani = Animation(N);
	float rot_x = 20;
	float rot_y = -30;
	float rot_z = 0;
	GLFWwindow *win;
	ROTATE_METHOD *operation;
	int op_count = 0;
	RubiksCube::Cube *cube;
	void reshape(GLFWwindow *win, int w, int h);
	void procKey();
	void drawBlock(const COLOR_NAME face[], int x, int y, int z);
	void drawPivot();
	void drawAnimation(Animation &ani);
	void display();
	void reshape(GLFWwindow *win, int w, int h)
	{
		if (h == 0)
			h = 1;
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, GLfloat(w) / h, 1, 100);
		glMatrixMode(GL_MODELVIEW);
	}
	
	void procKey()
	{
		if (glfwGetKey(win, GLFW_KEY_UP))
			rot_x -= 2;
		else if (glfwGetKey(win, GLFW_KEY_DOWN))
			rot_x += 2;
		else if (glfwGetKey(win, GLFW_KEY_LEFT))
			rot_y -= 2;
		else if (glfwGetKey(win, GLFW_KEY_RIGHT))
			rot_y += 2;
		else if (glfwGetKey(win, GLFW_KEY_ESCAPE))
			exit(EXIT_SUCCESS);
	}
	void startDisplay()
	{
		while (!glfwWindowShouldClose(win))
		{
			if (!op_count && !glfwGetKey(win, GLFW_KEY_SPACE) && !glfwGetKey(win, GLFW_KEY_ENTER))
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				ani = Animation(N);
				drawAnimation(ani);
				glfwSwapBuffers(win);
			}
			else
			{
				display();
			}
			procKey();
			glfwWaitEventsTimeout(1.0 / Animation::FPS);
		}
	}
	void drawBlock(const COLOR_NAME face[], int x, int y, int z)
	{
		glBegin(GL_QUADS);
		{
			// right
			if (face[RIGHT] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[RIGHT]]);
				glVertex3d(2 * x + 1, 2 * y + sticker_size, 2 * z + sticker_size);
				glVertex3d(2 * x + 1, 2 * y - sticker_size, 2 * z + sticker_size);
				glVertex3d(2 * x + 1, 2 * y - sticker_size, 2 * z - sticker_size);
				glVertex3d(2 * x + 1, 2 * y + sticker_size, 2 * z - sticker_size);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			
			// left
			if (face[LEFT] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[LEFT]]);
				glVertex3d(2 * x - 1, 2 * y + sticker_size, 2 * z + sticker_size);
				glVertex3d(2 * x - 1, 2 * y + sticker_size, 2 * z - sticker_size);
				glVertex3d(2 * x - 1, 2 * y - sticker_size, 2 * z - sticker_size);
				glVertex3d(2 * x - 1, 2 * y - sticker_size, 2 * z + sticker_size);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			
			// up
			if (face[UP] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[UP]]);
				glVertex3d(2 * x + sticker_size, 2 * y + 1, 2 * z + sticker_size);
				glVertex3d(2 * x + sticker_size, 2 * y + 1, 2 * z - sticker_size);
				glVertex3d(2 * x - sticker_size, 2 * y + 1, 2 * z - sticker_size);
				glVertex3d(2 * x - sticker_size, 2 * y + 1, 2 * z + sticker_size);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			
			// down
			if (face[DOWN] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[DOWN]]);
				glVertex3d(2 * x + sticker_size, 2 * y - 1, 2 * z + sticker_size);
				glVertex3d(2 * x - sticker_size, 2 * y - 1, 2 * z + sticker_size);
				glVertex3d(2 * x - sticker_size, 2 * y - 1, 2 * z - sticker_size);
				glVertex3d(2 * x + sticker_size, 2 * y - 1, 2 * z - sticker_size);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			
			// front
			if (face[FRONT] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[FRONT]]);
				glVertex3d(2 * x + sticker_size, 2 * y + sticker_size, 2 * z + 1);
				glVertex3d(2 * x - sticker_size, 2 * y + sticker_size, 2 * z + 1);
				glVertex3d(2 * x - sticker_size, 2 * y - sticker_size, 2 * z + 1);
				glVertex3d(2 * x + sticker_size, 2 * y - sticker_size, 2 * z + 1);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			
			// back
			if (face[BACK] != INVISIBLE)
			{
				glColor3ubv(Color3ub[face[BACK]]);
				glVertex3d(2 * x + sticker_size, 2 * y + sticker_size, 2 * z - 1);
				glVertex3d(2 * x + sticker_size, 2 * y - sticker_size, 2 * z - 1);
				glVertex3d(2 * x - sticker_size, 2 * y - sticker_size, 2 * z - 1);
				glVertex3d(2 * x - sticker_size, 2 * y + sticker_size, 2 * z - 1);
			}
			glColor3ubv(Color3ub[BLOCK]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
		}
		glEnd();
	}
	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAnimation(ani);
		if (ani.rotate_method == N)
		{
			char op;
			if ((op = operation[op_count]) != STOP)
			{
				op_count++;
				ani = Animation(static_cast<ROTATE_METHOD>(op));
			}
		}
		glfwSwapBuffers(win);
	}
	void initDisplay(const RubiksCube::Cube &cb)
	{
		cube = new RubiksCube::Cube(cb);
		if (!glfwInit())
			exit(EXIT_FAILURE);
		win = glfwCreateWindow(600, 500, "Rubik's Cube", NULL, NULL);
		if (win == nullptr)
			exit(EXIT_FAILURE);
		glfwSetWindowPos(win, 100, 100);
		glfwSetWindowSizeCallback(win, reshape);
		glfwMakeContextCurrent(win);
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClearDepth(1);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		//glEnable(GL_MULTISAMPLE);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, GLfloat(600) / 500, 1, 100);
		glMatrixMode(GL_MODELVIEW);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		GLfloat light_param[] = { 15.0, 15.0, 5.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_param);
		GLfloat light_spot[] = { -3, -3, -1, -1 };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot);
		GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		GLfloat light_specular[] = { 0.7, 0.55, 0.65, 1.0 };
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glEnable(GL_LIGHT0);
	}
	void drawAnimation(Animation &ani)
	{
		if ((ani.frame_count += Animation::STEP) > Animation::MAX_FRAME)
		{
			if (ani.rotate_method != N) cube->rotateLayer(ani.rotate_method);
				ani = Animation(N);
		}
		glLoadIdentity();
		glTranslatef(0, 0, -30);
		glRotatef(rot_x, 1, 0, 0);
		glRotatef(rot_y, 0, 1, 0);
		glRotatef(rot_z, 0, 0, 1);
		drawPivot();
		switch (ani.rotate_method)
		{
			case N:
				for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case X:
			case Xi:
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
				for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case R:
			case Ri:
				for_no_right(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
				for_right(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case L:
			case Li:
				for_no_left(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
				for_left(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case Y:
			case Yi:
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
				for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case U:
			case Ui:
				for_no_up(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
				for_up(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			
			case D:
			case Di:
				for_no_down(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
				for_down(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case Z:
			case Zi:
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
				for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case F:
			case Fi:
				for_no_front(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
				for_front(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;
			case B:
			case Bi:
				for_no_back(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
				for_back(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
				break;	
			default:
				break;
		}
	}
	
	void drawPivot()
	{
		glColor3ubv(Color3ub[PIVOT]);
		glBegin(GL_QUADS);
		{
			// right
			glVertex3d(pivot_size, pivot_size, pivot_size);
			glVertex3d(pivot_size, -pivot_size, pivot_size);
			glVertex3d(pivot_size, -pivot_size, -pivot_size);
			glVertex3d(pivot_size, pivot_size, -pivot_size);
			
			// left
			glVertex3d(-pivot_size, pivot_size, pivot_size);
			glVertex3d(-pivot_size, pivot_size, -pivot_size);
			glVertex3d(-pivot_size, -pivot_size, -pivot_size);
			glVertex3d(-pivot_size, -pivot_size, pivot_size);
			
			// up
			glVertex3d(pivot_size, pivot_size, pivot_size);
			glVertex3d(pivot_size, pivot_size, -pivot_size);
			glVertex3d(-pivot_size, pivot_size, -pivot_size);
			glVertex3d(-pivot_size, pivot_size, pivot_size);
			
			// down
			glVertex3d(pivot_size, -pivot_size, pivot_size);
			glVertex3d(-pivot_size, -pivot_size, pivot_size);
			glVertex3d(-pivot_size, -pivot_size, -pivot_size);
			glVertex3d(pivot_size, -pivot_size, -pivot_size);
			
			// front
			glVertex3d(pivot_size, pivot_size, pivot_size);
			glVertex3d(-pivot_size, pivot_size, pivot_size);
			glVertex3d(-pivot_size, -pivot_size, pivot_size);
			glVertex3d(pivot_size, -pivot_size, pivot_size);
			
			// back
			glVertex3d(pivot_size, pivot_size, -pivot_size);
			glVertex3d(pivot_size, -pivot_size, -pivot_size);
			glVertex3d(-pivot_size, -pivot_size, -pivot_size);
			glVertex3d(-pivot_size, pivot_size, -pivot_size);
		}
		glEnd();
	}
	void loadOperation(const ROTATE_METHOD *s)
	{
		//operation = s;
	}
}