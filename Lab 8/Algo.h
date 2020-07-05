#pragma once
#include <memory>
#include <vector>
#include "Cube.h"

using move_step_t = std::pair<Face::FACE_TYPE, int>;
using move_seq_t = std::vector<move_step_t>;

class Algo
{
public:
	virtual ~Algo() = default;
	virtual void init(const char* = nullptr) = 0;
	virtual move_seq_t solve(Cube) const = 0;
};

std::unique_ptr<Algo> createKociembaAlgo(int = 1);
	