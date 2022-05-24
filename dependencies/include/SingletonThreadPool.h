#pragma once
#include "ThreadPool.h"

namespace Threading {
	template <uint32_t threadsCount>
	class THREAD_POOL_API SingletonThreadPool final {
	private:
		ThreadPool threadPool;

		SingletonThreadPool() : threadPool(threadsCount) {};
		~SingletonThreadPool() = default;
	public:
		static SingletonThreadPool<threadsCount>& get() {
			static SingletonThreadPool<threadsCount> instance;
			return instance;
		}

		void addTask(const std::function<void()>& task, const std::function<void()>& callback = nullptr) {
			threadPool.addTask(task, callback);
		}

		void addTask(std::function<void()>&& task, const std::function<void()>& callback = nullptr) {
			threadPool.addTask(std::move(task), callback);
		}

		void reinit() {
			threadPool.reinit();
		}

		void shutdown() {
			threadPool.shutdown();
		}

		bool isAnyTaskRunning() const {
			threadPool.isAnyTaskRunning();
		}

		uint32_t getThreadsCount() const {
			return threadsCount;
		}
	};
}