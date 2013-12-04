#include <Engine/Challenge.h>
#include <Engine/Core/Dispatch.h>

namespace challenge
{
	TDispatchQueueMap Dispatch::sDispatchQueues;
	const std::string Dispatch::MainQueue = "__MAIN_DISPATCH_QUEUE__";

	void Dispatch::PushTask(const std::string &queue, TDispatchFunction task)
	{
		sDispatchQueues[queue].push_back(task);
	}

	void Dispatch::ExecuteQueue(const std::string &queue, bool empty)
	{
		TDispatchQueue &tasks = sDispatchQueues[queue];
		for (TDispatchFunction function : tasks) {
			function();
		}

		if (empty) {
			tasks.clear();
		}
	}
}