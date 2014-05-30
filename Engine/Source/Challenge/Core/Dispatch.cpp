#include <Challenge/Challenge.h>
#include <Challenge/Core/Dispatch.h>

namespace challenge
{
	SafeObject<TDispatchQueueMap> Dispatch::sDispatchQueues;
	const std::string Dispatch::MainQueue = "__MAIN_DISPATCH_QUEUE__";

	static std::recursive_mutex mutex;

	void Dispatch::PushTask(const std::string &queue, TDispatchFunction task)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex);

		sDispatchQueues[queue].push_back(task);
	}

	void Dispatch::ExecuteQueue(const std::string &queue, bool empty)
	{
		std::lock_guard<std::recursive_mutex> lock(mutex);

		TDispatchQueue tasks = sDispatchQueues[queue];
		for (TDispatchFunction function : tasks) {
			function();
		}

		if (empty) {
			sDispatchQueues[queue].clear();
		}
	}
}