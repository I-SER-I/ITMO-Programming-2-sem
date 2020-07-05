#define GL_SILENCE_DEPRECATION
#include "Viewer.h"
#include <GLFW/glfw3.h>
#include <GLFW/glut.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <tuple>
#include "Algo.h"
#include "Rotation.h"

class RotateManager
{
public:
	RotateManager() : active(false)
	{
	}

	bool isActive() { return active; }

	double get()
	{
		std::chrono::duration<double> rate = clock_type::now() - time_point;
		double r = rate.count() / t;
		if (r >= 1.0) active = false;
		return r;
	}

	void set(double duration)
	{
		time_point = clock_type::now();
		t = duration;
		active = true;
	}

private:
	using clock_type = std::chrono::system_clock;
	std::chrono::time_point<clock_type> time_point;
	double t;
	bool active;
};

class ViewerGl : public Viewer
{
public:
	ViewerGl();
	~ViewerGl() = default;
	bool init();
	void run();
	void setCube(const Cube&);
	void setRotateDuration(double);
	void addRotate(Face::FACE_TYPE, int);
	void addRotate(Face::FACE_TYPE, int, int);
	void solveCube(Cube&);
	bool checkCurrentState(Cube&);

private:
	void drawCube(const Cube&);
	void drawBlock(GLfloat, GLfloat, GLfloat, GLfloat, Block, GLenum);
	void updateRotate();
	void setColor(int);
	static void keyCallback(GLFWwindow*, int, int, int, int);
	static void mouseButtonCallback(GLFWwindow*, int, int, int);
	using rotate_que_t = std::tuple<Face::FACE_TYPE, int, int>;
	std::queue<rotate_que_t> rotateQueue;
	int rotateMask[3];
	GLfloat rotateDeg, rotateVec;
	RotateManager rotateManager;
	double rotateDuration;
	VirtualOrb vOrb;
	Cube cube;
	GLFWwindow* window;
};

ViewerGl::ViewerGl()
{
	window = nullptr;
	rotateDuration = 1;
	rotateDeg = rotateVec = 0;
	std::fill(rotateMask, rotateMask + 3, -1);
}

bool ViewerGl::init()
{
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(600, 600, "I_SER_I's Rubik's Cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	glfwMakeContextCurrent(window);
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	vOrb.setRotate(45, {-1, 1, 0});

	return true;
}

void ViewerGl::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateRotate();
		drawCube(cube);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}

void ViewerGl::setCube(const Cube& cube) { this->cube = cube; }

void ViewerGl::addRotate(Face::FACE_TYPE type, int cnt)
{
	addRotate(type, 1, cnt);
}

void ViewerGl::addRotate(Face::FACE_TYPE type, int depth, int cnt)
{
	rotateQueue.push({type, depth, cnt % 4});
}

void ViewerGl::updateRotate()
{
	if (rotateQueue.empty()) return;

	Face::FACE_TYPE ftype;
	int depth, cnt;
	std::tie(ftype, depth, cnt) = rotateQueue.front();

	if (!rotateManager.isActive())
	{
		rotateManager.set(rotateDuration);
		std::fill(rotateMask, rotateMask + 3, -1);

		rotateVec = cnt < 0 ? -1 : 1;

		switch (ftype)
		{
		case Face::top:
			rotateMask[0] = 3 - depth;
			break;
		case Face::bottom:
			rotateMask[0] = depth - 1;
			rotateVec = -rotateVec;
			break;
		case Face::left:
			rotateMask[2] = depth - 1;
			rotateVec = -rotateVec;
			break;
		case Face::right:
			rotateMask[2] = 3 - depth;
			break;
		case Face::front:
			rotateMask[1] = 3 - depth;
			rotateVec = -rotateVec;
			break;
		case Face::back:
			rotateMask[1] = depth - 1;
			break;
		}
	}

	double rate = rotateManager.get();
	rotateDeg = std::abs(cnt) * 90.0 * rate;

	if (!rotateManager.isActive())
	{
		std::fill(rotateMask, rotateMask + 3, -1);
		cube.rotate(ftype, cnt);
		rotateQueue.pop();
	}
}

void outRotate(int c1, int c2)
{
	const char* face_str = "UDFBLR";
	std::putchar(face_str[c1]);
	if (c2 > 1) std::putchar(c2 == 2 ? '2' : '\'');
}

void ViewerGl::solveCube(Cube& c)
{
	ViewerGl* viewer =
		reinterpret_cast<ViewerGl*>(glfwGetWindowUserPointer(window));

	auto algo = createKociembaAlgo(4);
	algo->init();
	move_seq_t ans = algo->solve(c);

	std::cout << "Solution: ";
	for (auto x : ans)
	{
		outRotate(int(x.first), (x.second % 4 + 4) & 3);
		viewer->addRotate(x.first, x.second);
	}
	std::cout << "\nThis solution needs " << ans.size() << " steps." << std::endl;
}

bool ViewerGl::checkCurrentState(Cube& c)
{
	auto algo = createKociembaAlgo(4);
	algo->init();
	move_seq_t ans = algo->solve(c);
	return c.isSolved();
}

void ViewerGl::setColor(int type)
{
	static const GLfloat colors[7][3] = {
		{0.0f, 1.0f, 0.0f}, // top    (green)
		{0.3f, 0.3f, 1.0f}, // bottom (blue)
		{1.0f, 0.3f, 0.3f}, // front  (red)
		{1.0f, 0.5f, 0.0f}, // back   (orange)
		{1.0f, 1.0f, 0.0f}, // left   (yellow)
		{1.0f, 1.0f, 1.0f}, // right  (white)
		{0.0f, 0.0f, 0.0f}  // frame
	};

	const GLfloat* C = colors[type];
	glColor3f(C[0], C[1], C[2]);
}

void ViewerGl::keyCallback(GLFWwindow* window, int key, int scancode,
                           int action, int mods)
{
	ViewerGl* viewer =
		reinterpret_cast<ViewerGl*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case '1':
			viewer->cube.read();
			break;
		case '9':
			viewer->cube.read("cube_state_wrong.txt");
			break;
		case '0':
			viewer->cube.read("cube_state_solved.txt");
			break;
		case '2':
			viewer->cube.write();
			break;
		case 'R':
			viewer->addRotate(Face::right, 1);
			break;
		case 'L':
			viewer->addRotate(Face::left, 1);
			break;
		case 'U':
			viewer->addRotate(Face::top, 1);
			break;
		case 'D':
			viewer->addRotate(Face::bottom, 1);
			break;
		case 'F':
			viewer->addRotate(Face::front, 1);
			break;
		case 'B':
			viewer->addRotate(Face::back, 1);
			break;
		case 'G':
			viewer->cube.generateCube();
			break;
		case 'S':
			viewer->solveCube(viewer->cube);
			break;
		case 'C':
			std::cout << "Is cube's current state correct? " << std::boolalpha
				<< viewer->checkCurrentState(viewer->cube) << std::endl;
			break;
		default:
			break;
		}
	}
}

void ViewerGl::mouseButtonCallback(GLFWwindow* window, int button, int action,
                                   int mods)
{
	ViewerGl* viewer =
		reinterpret_cast<ViewerGl*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		viewer->cube.printCurrentState();
}

void ViewerGl::setRotateDuration(double sec) { rotateDuration = sec; }

void ViewerGl::drawBlock(GLfloat x, GLfloat y, GLfloat z, GLfloat s,
                         Block color, GLenum type)
{
	setColor(color.back);
	glBegin(type);
	glVertex3f(x, y, z);
	glVertex3f(x, y + s, z);
	glVertex3f(x + s, y + s, z);
	glVertex3f(x + s, y, z);
	glEnd();

	setColor(color.front);
	glBegin(type);
	glVertex3f(x, y, z - s);
	glVertex3f(x, y + s, z - s);
	glVertex3f(x + s, y + s, z - s);
	glVertex3f(x + s, y, z - s);
	glEnd();

	setColor(color.top);
	glBegin(type);
	glVertex3f(x, y + s, z);
	glVertex3f(x + s, y + s, z);
	glVertex3f(x + s, y + s, z - s);
	glVertex3f(x, y + s, z - s);
	glEnd();

	setColor(color.bottom);
	glBegin(type);
	glVertex3f(x, y, z);
	glVertex3f(x + s, y, z);
	glVertex3f(x + s, y, z - s);
	glVertex3f(x, y, z - s);
	glEnd();

	setColor(color.left);
	glBegin(type);
	glVertex3f(x, y, z);
	glVertex3f(x, y + s, z);
	glVertex3f(x, y + s, z - s);
	glVertex3f(x, y, z - s);
	glEnd();

	setColor(color.right);
	glBegin(type);
	glVertex3f(x + s, y, z);
	glVertex3f(x + s, y + s, z);
	glVertex3f(x + s, y + s, z - s);
	glVertex3f(x + s, y, z - s);
	glEnd();
}

void ViewerGl::drawCube(const Cube& cube)
{
	class RotateGuard
	{
		bool isRotated;

	public:
		RotateGuard(int mask, int real, GLfloat deg, GLfloat X, GLfloat Y,
		            GLfloat Z)
		{
			if (mask == real)
			{
				isRotated = true;
				glPushMatrix();
				glRotatef(deg, X, Y, Z);
			}
			else
				isRotated = false;
		}

		~RotateGuard()
		{
			if (isRotated) glPopMatrix();
		}
	};

	GLfloat size = 0.8f / 3;

	glPushMatrix();

	vOrb.rotate();
	glLineWidth(1.5f);

	GLfloat base = -size * 3 * 0.5f, x, y, z;
	static_cast<void>(x = y = base), z = -base;

	for (int i = 0; i != 3; ++i, y += size, x = base, z = -base)
	{
		RotateGuard _guard(rotateMask[0], i, rotateDeg, 0, rotateVec, 0);
		for (int j = 0; j != 3; ++j, z -= size, x = base)
		{
			RotateGuard _guard(rotateMask[1], j, rotateDeg, 0, 0, rotateVec);
			for (int k = 0; k != 3; ++k, x += size)
			{
				RotateGuard _guard(rotateMask[2], k, rotateDeg, rotateVec, 0, 0);
				drawBlock(x, y, z, size, cube.getBlock(i, j, k), GL_QUADS);
				drawBlock(x, y, z, size, {6, 6, 6, 6, 6, 6}, GL_LINE_LOOP);
			}
		}
	}

	glPopMatrix();
}

std::unique_ptr<Viewer> createOpenglViewer()
{
	return std::make_unique<ViewerGl>();
}
