#pragma once
#include <memory>
#include "Cube.h"

class Viewer
{
public:
	virtual ~Viewer() = default;
	virtual void run() = 0;
	virtual bool init() = 0;
	virtual void setCube(const Cube&) = 0;
	virtual void setRotateDuration(double) = 0;
	virtual void addRotate(Face::FACE_TYPE, int) = 0;
	virtual void addRotate(Face::FACE_TYPE, int, int) = 0;
	virtual void solveCube(Cube&) = 0;
};

std::unique_ptr<Viewer> createOpenglViewer();
