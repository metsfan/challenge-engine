#pragma once

#include <functional>
#include <map>
#include <vector>

#include <Challenge/Util/SafeObject.hpp>

namespace challenge
{
	typedef std::function<void()> TDispatchFunction;
	typedef std::vector<TDispatchFunction> TDispatchQueue;
	typedef std::map<std::string, TDispatchQueue> TDispatchQueueMap;


	class Dispatch
	{
	public:
		static void PushTask(const std::string &queue, TDispatchFunction task);

		static void ExecuteQueue(const std::string &queue, bool empty = true);

		static SafeObject<TDispatchQueueMap> sDispatchQueues;

		static const std::string MainQueue;
	};
	
}