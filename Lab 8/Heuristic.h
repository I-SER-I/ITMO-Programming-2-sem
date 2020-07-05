#pragma once
#include <cstdint>
#include <queue>
#include <vector>
#include "Cube.h"

constexpr static int DISALLOW_FACES[6] = {-1, 0, -1, 2, -1, 4};
constexpr static int FACTORIAL_4[] = {1, 4, 12, 24};
constexpr static int FACTORIAL_8[] = {1, 8, 56, 336, 1680, 6720, 20160, 40320};
constexpr static int FACTORIAL_12[] = {
	1, 12, 132, 1320, 11880, 95040,
	665280, 3991680, 19958400, 79833600, 239500800, 479001600
};

template <int N, int S>
int encodePerm(const int8_t* p, const int* k)
{
	int pos[N], elem[N];
	for (int i = 0; i != N; ++i) pos[i] = elem[i] = i;
	int v = 0, t;
	for (int i = 0; i != S; ++i)
	{
		t = pos[p[i]];
		v += k[i] * t;
		pos[elem[N - i - 1]] = t;
		elem[t] = elem[N - i - 1];
	}

	return v;
}

template <bool IsGroup1, bool RecordState = false>
void initHeuristic(int8_t* buf, int (*encoder)(const Cube&),
                          std::vector<Cube>* recorder = nullptr,
                          const std::vector<Cube>& initState = {Cube()})
{
	std::queue<std::pair<Cube, uint8_t>> queue;

	for (const Cube& c : initState)
	{
		buf[(*encoder)(c)] = 0;
		queue.push({c, 0 | (6 << 4)});
	}

	while (!queue.empty())
	{
		auto u = queue.front();
		int face = u.second >> 4;
		int step = u.second & 0xf;

		for (int i = 0; i != 6; ++i)
		{
			if (i == face || DISALLOW_FACES[i] == face) continue;

			Cube c = u.first;
			for (int j = 0; j != 3; ++j)
			{
				if (IsGroup1 && i >= 2)
				{
					if (j) break;
					c.rotate(Face::FACE_TYPE(i), 2);
				}
				else
					c.rotate(Face::FACE_TYPE(i), 1);

				int code = (*encoder)(c);
				if (buf[code] == -1)
				{
					buf[code] = step + 1;
					queue.push({c, (step + 1) | (i << 4)});
					if (RecordState) recorder->push_back(c);
				}
			}
		}

		queue.pop();
	}
}
