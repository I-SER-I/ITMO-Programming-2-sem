#pragma once
#include <cstdint>
#include <utility>

struct Face
{
	enum FACE_TYPE
	{
		top,
		bottom,
		front,
		back,
		left,
		right,
	};
	int8_t C[9];
};
struct Block
{
	int8_t top, bottom, front, back, left, right;
};
using block_info_t = std::pair<const int8_t*, const int8_t*>;

/*
 * observing from the top face, the index of corners will be like this
 *     *-*-*-*        *-*-*-*
 *     |0| |1|        |4| |5|
 *     *-*-*-*        *-*-*-*
 *     | | | |        | | | |
 *     *-*-*-*        *-*-*-*
 *     |3| |2|        |7| |6|
 *     *-*-*-*        *-*-*-*
 * the bottom face, the top face
 *
 * observing from the top face, the index of edges will be like this
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     | |8| |          |0| |1|         | |4| |
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     |B| |9|          | | | |         |7| |5|
 *     *-*-*-*          *-*-*-*         *-*-*-*
 *     | |A| |          |3| |2|         | |6| |
 *     *-*-*-*          *-*-*-*         *-*-*-*
 * the bottom face, the middle level, the top face
 *
 * the priority of the key faces: UD > LR > FB
 *
 */
class Cube
{
public:
	Cube();
	/* look from the top face
	 * *-----------------*
	 * |(0,0) (0,1) (0,2)|
	 * |(1,0) (1,1) (1,2)|
	 * |(2,0) (2,1) (2,2)|
	 * *-----------------*
	 *
	 * bottom level = 0
	 * middle level = 1
	 * top level = 2
	 */
	Block getBlock(int, int, int) const;
	block_info_t getCornerBlock() const;
	block_info_t getEdgeBlock() const;
	bool isSolved();
	void read(const char* = "cube_state.txt");
	void write();
	void printCurrentState();
	void generateCube();
	void rotate(Face::FACE_TYPE, int = 1);
private:
	int8_t cp[8], co[8]; // corners' position and orientation
	int8_t ep[12], eo[12]; // edges' position and orientation
};
