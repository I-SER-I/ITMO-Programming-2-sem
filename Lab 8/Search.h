#pragma once
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include "Cube.h"

struct SearchInfo
{
	Cube cb;
	int g, face, depth;

	move_seq_t* seq;

	int tid;
	std::atomic<int>* resultId;
};

template <typename SearchFunc>
inline bool searchMultiThread(int threadNum, const SearchInfo& s,
                              SearchFunc search)
{
	SearchInfo infos[18];
	move_seq_t seqs[18];

	std::mutex cvMtx;
	std::condition_variable cv;
	int workingThread = 0;

	std::future<bool> results[18];
	std::atomic<int> resultId;
	resultId = -1;

	for (int i = 0; i != 6; ++i)
	{
		Cube cube = s.cb;
		for (int j = 1; j <= 3; ++j)
		{
			int id = i * 3 + j - 1;
			cube.rotate(Face::FACE_TYPE(i), 1);

			seqs[id].resize(s.depth);
			seqs[id][0] = move_step_t{Face::FACE_TYPE(i), j};

			infos[id] = s;
			infos[id].tid = id;
			infos[id].cb = cube;
			infos[id].seq = seqs + id;
			infos[id].g = 1;
			infos[id].face = i;
			infos[id].resultId = &resultId;

			std::packaged_task<bool()> task{
				[&, id]() -> bool
				{
					std::unique_lock<std::mutex> lk(cvMtx);
					cv.wait(lk, [&] { return workingThread < threadNum; });

					++workingThread;
					lk.unlock();

					bool ret = search(infos[id]);

					{
						std::lock_guard<std::mutex> lk(cvMtx);
						--workingThread;
					}

					cv.notify_one();

					return ret;
				}
			};

			results[id] = task.get_future();

			std::thread{std::move(task)}.detach();
		}
	}

	cv.notify_all();

	for (auto& fu : results) fu.wait();

	if (resultId >= 0)
	{
		*s.seq = seqs[resultId];
		return true;
	}
	else
		return false;
}
