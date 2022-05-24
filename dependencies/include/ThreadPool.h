#pragma once
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <vector>
#include <memory>
#include <functional>

#ifdef THREAD_POOL_DLL
#define THREAD_POOL_API __declspec(dllexport)
#else
#define THREAD_POOL_API
#endif

namespace Threading {
	class THREAD_POOL_API ThreadPool final {
	private:
		struct ThreadPoolTask {
			std::function<void()> task;
			std::function<void()> callback;
		public:
			ThreadPoolTask() = default;
			ThreadPoolTask(const ThreadPoolTask& obj);
			ThreadPoolTask(ThreadPoolTask&& obj) noexcept;
			~ThreadPoolTask() = default;

			ThreadPoolTask& operator=(const ThreadPoolTask& obj);
			ThreadPoolTask& operator=(ThreadPool&& obj) noexcept;
		};
	private:
		std::queue<ThreadPoolTask> tasks;
		std::condition_variable hasTask;
		std::mutex tasksMutex;

		std::vector<std::unique_ptr<std::thread>> threads;
		std::vector<bool> threadsState;

		uint32_t threadsCount;
		bool terminate;

		void mainWorkerThread(size_t threadIndex);
	public:
		ThreadPool(uint32_t threadsCount = std::thread::hardware_concurrency());

		void addTask(const std::function<void()>& task, const std::function<void()>& callback = nullptr);
		void addTask(std::function<void()>&& task, const std::function<void()>& callback = nullptr);

		void reinit(bool changeThreadsCount = false, uint32_t threadsCount = std::thread::hardware_concurrency());
		void shutdown();

		bool isAnyTaskRunning() const;

		uint32_t getThreadsCount() const;

		~ThreadPool();
	};
}
