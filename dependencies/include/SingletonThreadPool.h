#pragma once
#include "ThreadPool.h"

namespace Threading {
    template <uint32_t threadsCount>
	class THREAD_POOL_API SingletonThreadPool final {
	private:
		ThreadPool threadPool;

		SingletonThreadPool();
		~SingletonThreadPool() = default;
	public:
	    static SingletonThreadPool& get();

        void addTask(const std::function<void()>& task, const std::function<void()>& callback = nullptr);
        void addTask(std::function<void()>&& task, const std::function<void()>& callback = nullptr);

        void reinit();
        void shutdown();

        bool isAnyTaskRunning() const;
        uint32_t getThreadsCount() const;
	};

    template <uint32_t threadsCount>
    SingletonThreadPool<threadsCount>::SingletonThreadPool()
        : threadPool(threadsCount)
    {

    }

    template<uint32_t threadsCount>
    SingletonThreadPool<threadsCount> &SingletonThreadPool<threadsCount>::get() {
        static SingletonThreadPool<threadsCount> _obj;
        return _obj;
    }

    template<uint32_t threadsCount>
    void SingletonThreadPool<threadsCount>::addTask(const std::function<void()> &task, const std::function<void()> &callback) {
        threadPool.addTask(task, callback);
    }

    template<uint32_t threadsCount>
    void SingletonThreadPool<threadsCount>::addTask(std::function<void()> &&task, const std::function<void()> &callback) {
        threadPool.addTask(std::move(task), callback);
    }

    template<uint32_t threadsCount>
    void SingletonThreadPool<threadsCount>::reinit() {
        threadPool.reinit();
    }

    template<uint32_t threadsCount>
    void SingletonThreadPool<threadsCount>::shutdown() {
        threadPool.shutdown();
    }

    template<uint32_t threadsCount>
    bool SingletonThreadPool<threadsCount>::isAnyTaskRunning() const {
        threadPool.isAnyTaskRunning();
    }

    template<uint32_t threadsCount>
    uint32_t SingletonThreadPool<threadsCount>::getThreadsCount() const {
        return threadsCount;
    }


}