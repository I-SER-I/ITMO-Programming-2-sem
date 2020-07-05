#pragma once
#include "Algo.h"
#include "Cube.h"
#include "Heuristic.h"
#include "Search.h"

class Kociemba : public Algo
{
public:
	Kociemba(int);
	~Kociemba() = default;
	void init(const char*);
	move_seq_t solve(Cube) const;
private:
	static int encodePhase1Edges(const Cube&);
	static int encodePhase1Co(const Cube&);
	static int encodePhase1Eo(const Cube&);
	static int encodePhase2Corners(const Cube&);
	static int encodePhase2Edges1(const Cube&);
	static int encodePhase2Edges2(const Cube&);
	template <int Size, typename PushFunc>
	static void initPermutation(int, int8_t*, const PushFunc&, int);
	template <int Phase>
	bool searchPhase(const SearchInfo&) const;
	template <int Phase>
	int estimate(const Cube&) const;
	int estimatePhase1(const Cube&) const;
	int estimatePhase2(const Cube&) const;
	static const int phase2CornersSize = 40320; // 8!
	static const int phrase2Edges1Size = 40320; // 8!
	static const int phrase2Edges2Size = 24; // 4!
	static const int phrase1EdgesSize = 12 * 11 * 10 * 9 * 16;
	static const int phrase1CoSize = 6561;
	static const int phrase1EoSize = 1 << 8;
	int8_t phrase2Corners[phase2CornersSize];
	int8_t phrase2Edges1[phrase2Edges1Size];
	int8_t phrase2Edges2[phrase2Edges2Size];
	int8_t phrase1Edges[phrase1EdgesSize];
	int8_t phrase1Co[phrase1CoSize];
	int8_t phrase1Eo[phrase1EoSize];
	int threadNum;
};

std::unique_ptr<Algo> createKociembaAlgo(int);
