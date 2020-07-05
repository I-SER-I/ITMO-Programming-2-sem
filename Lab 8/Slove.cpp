#include <cstring>
#include <functional>
#include "Slove.h"

Kociemba::Kociemba(int threadNum) { this->threadNum = threadNum; }

template <int Size, typename PushFunc>
void Kociemba::initPermutation(int now, int8_t* v, const PushFunc& push,
                               int avail)
{
	if (!avail) return push();

	for (int i = 0; i != Size; ++i)
	{
		if ((avail >> i) & 1)
		{
			avail ^= 1 << i;
			v[now] = i;
			initPermutation<Size>(now + 1, v, push, avail);
			avail ^= 1 << i;
		}
	}
}

void Kociemba::init(const char*)
{
	std::vector<Cube> states;

	std::memset(phrase2Corners, 0xff, sizeof(phrase2Corners));
	initHeuristic<true>(phrase2Corners, &Kociemba::encodePhase2Corners);

	std::memset(phrase2Edges1, 0xff, sizeof(phrase2Edges1));
	initHeuristic<true>(phrase2Edges1, &Kociemba::encodePhase2Edges1);

	std::memset(phrase2Edges2, 0xff, sizeof(phrase2Edges2));
	initHeuristic<true, true>(phrase2Edges2, &Kociemba::encodePhase2Edges2,
	                          &states);

	for (Cube& c : states)
	{
		// fix the orientation
		int8_t* eo = const_cast<int8_t*>(c.getEdgeBlock().second);
		eo[0] = eo[1] = eo[2] = eo[3] = 0;
	}

	std::memset(phrase1Edges, 0xff, sizeof(phrase1Edges));
	initHeuristic<false>(phrase1Edges, &Kociemba::encodePhase1Edges, nullptr,
	                     states);

	states.clear();

	Cube cube0;
	int8_t* cube0Ep = const_cast<int8_t*>(cube0.getCornerBlock().first);
	initPermutation<8>(
		0, cube0Ep, [&]() { states.push_back(cube0); }, (1 << 8) - 1);

	std::memset(phrase1Co, 0xff, sizeof(phrase1Co));
	initHeuristic<false>(phrase1Co, &Kociemba::encodePhase1Co, nullptr, states);

	states.clear();
	cube0 = Cube();

	initPermutation<12>(
		4, cube0Ep, [&]() { states.push_back(cube0); }, ((1 << 8) - 1) << 4);

	std::memset(phrase1Eo, 0xff, sizeof(phrase1Eo));
	initHeuristic<false>(phrase1Eo, &Kociemba::encodePhase1Eo, nullptr, states);
}

move_seq_t Kociemba::solve(Cube cb) const
{
	if (cb.isSolved()) return {};

	move_seq_t solution;

	// phase 1
	for (int depth = 0;; ++depth)
	{
		move_seq_t seq(depth);

		SearchInfo s;
		s.cb = cb;
		s.g = 0;
		s.seq = &seq;
		s.face = 6;
		s.depth = depth;

		if (depth < 7 || threadNum == 1)
		{
			s.tid = -1;
			if (searchPhase<1>(s))
			{
				solution = *s.seq;
				break;
			}
		}
		else
		{
			using namespace std::placeholders;
			if (searchMultiThread(threadNum, s,
			                      std::bind(&Kociemba::searchPhase<1>, this, _1)))
			{
				solution = *s.seq;
				break;
			}
		}
	}

	for (move_step_t& step : solution) cb.rotate(step.first, step.second);

	// phase 2
	for (int depth = 0;; ++depth)
	{
		move_seq_t seq(depth);

		SearchInfo s;
		s.cb = cb;
		s.g = 0;
		s.seq = &seq;
		s.face = 6;
		s.depth = depth;
		s.tid = -1;

		if (searchPhase<2>(s))
		{
			if (seq.front().first == solution.back().first)
			{
				// merge rotation of same faces;
				seq[0].second = (seq[0].second + solution.back().second) % 4;
				solution.pop_back();
			}

			for (move_step_t step : seq) solution.push_back(step);
			break;
		}
	}

	for (move_step_t& step : solution)
		if (step.second == 3) step.second = -1;

	return solution;
}

template <int Phase>
bool Kociemba::searchPhase(const SearchInfo& s) const
{
	if (s.tid >= 0 && *s.resultId >= 0) return true;

	SearchInfo t = s;
	t.g += 1;

	for (int i = 0; i != 6; ++i)
	{
		if (i == s.face || DISALLOW_FACES[i] == s.face) continue;

		Cube cube = s.cb;
		for (int j = 1; j <= 3; ++j)
		{
			if (Phase == 1)
				cube.rotate(Face::FACE_TYPE(i), 1);
			else
			{
				if (i >= 2 && j != 2) continue;
				cube.rotate(Face::FACE_TYPE(i), i < 2 ? 1 : j);
			}

			int h = estimate<Phase>(cube);
			if (h + s.g + 1 <= s.depth)
			{
				(*s.seq)[s.g] = move_step_t{Face::FACE_TYPE(i), j};

				if (h == 0)
				{
					if (s.tid >= 0) *s.resultId = s.tid;
					return true;
				}

				t.cb = cube;
				t.face = i;

				if (searchPhase<Phase>(t)) return true;
			}
		}
	}

	return false;
}

template <int Phase>
int Kociemba::estimate(const Cube& c) const
{
	if (Phase == 1) return estimatePhase1(c);
	return estimatePhase2(c);
}

int Kociemba::estimatePhase1(const Cube& c) const
{
	return std::max(
		phrase1Edges[encodePhase1Edges(c)],
		std::max(phrase1Eo[encodePhase1Eo(c)], phrase1Co[encodePhase1Co(c)]));
}

int Kociemba::estimatePhase2(const Cube& c) const
{
	return std::max(phrase2Corners[encodePhase2Corners(c)],
	                std::max(phrase2Edges1[encodePhase2Edges1(c)],
	                         phrase2Edges2[encodePhase2Edges2(c)]));
}

int Kociemba::encodePhase2Corners(const Cube& c)
{
	block_info_t cb = c.getCornerBlock();
	return encodePerm<8, 7>(cb.first, FACTORIAL_8);
}

int Kociemba::encodePhase2Edges1(const Cube& c)
{
	block_info_t eb = c.getEdgeBlock();
	int8_t perm[8];
	for (int i = 4; i != 12; ++i) perm[i - 4] = eb.first[i] - 4;

	return encodePerm<8, 7>(perm, FACTORIAL_8);
}

int Kociemba::encodePhase2Edges2(const Cube& c)
{
	block_info_t eb = c.getEdgeBlock();
	return encodePerm<4, 3>(eb.first, FACTORIAL_4);
}

int Kociemba::encodePhase1Edges(const Cube& c)
{
	block_info_t eb = c.getEdgeBlock();
	int v = 0;
	int8_t perm[4];
	for (int i = 0; i != 12; ++i)
		if (eb.first[i] < 4)
		{
			perm[eb.first[i]] = i;
			v |= eb.second[i] << eb.first[i];
		}

	return v | (encodePerm<12, 4>(perm, FACTORIAL_12) << 4);
}

int Kociemba::encodePhase1Co(const Cube& c)
{
	static const int base[] = {1, 3, 9, 27, 81, 243, 729, 2187};
	block_info_t cb = c.getCornerBlock();
	int v = 0;
	for (int i = 0; i != 8; ++i) v += cb.second[i] * base[i];
	return v;
}

int Kociemba::encodePhase1Eo(const Cube& c)
{
	block_info_t eb = c.getEdgeBlock();
	int v = 0;
	for (int i = 0; i != 8; ++i) v |= eb.second[i + 4] << i;
	return v;
}

std::unique_ptr<Algo> createKociembaAlgo(int threadNum)
{
	return std::make_unique<Kociemba>(threadNum);
}
