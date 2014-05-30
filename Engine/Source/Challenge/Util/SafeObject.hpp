#pragma once

#include <mutex>

namespace challenge
{
	template <typename T>
	class SafeObject : public T
	{
	public:

		SafeObject<T>()
			: T(), m_mutex()
		{
		}

		SafeObject<T>(const SafeObject<T>& other) :
			T(other), m_mutex()
		{
		}

		void lock()
		{
			m_mutex.lock();
		}

		void unlock()
		{
			m_mutex.unlock();
		}

		bool tryLock()
		{
			m_mutex.try_lock();
		}

	private:

		std::recursive_mutex m_mutex;

	};
}