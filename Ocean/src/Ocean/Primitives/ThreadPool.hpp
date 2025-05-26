/**
 * @file ThreadPool.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"

#include "Ocean/Primitives/DynamicArray.hpp"

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>

typedef std::function<void()> VoidFunction;

class ThreadPool {
public:
    explicit ThreadPool(u16 threadCount = std::thread::hardware_concurrency()) :
        m_Workers(threadCount),
        m_Tasks(),
        m_QueueMutex(),
        m_Condition(),
        m_Stop(false)
    {
        Start(threadCount);
    }
    ~ThreadPool()
    {

    }

    void Enqueue(VoidFunction task) {
        {
            std::unique_lock<std::mutex> lock(this->m_QueueMutex);

            this->m_Tasks.push(std::move(task));
        }

        this->m_Condition.notify_one();
    }

private:
    void Start(sizet threadCount) {
        for (u16 i = 0; i < threadCount; i++) {
            this->m_Workers.EmplaceBack([this] {
                while (true) {
                    VoidFunction task;

                    {
                        std::unique_lock<std::mutex> lock(this->m_QueueMutex);
                        this->m_Condition.wait(lock, [this] {
                            return this->m_Stop || !this->m_Tasks.empty();
                        });

                        if (this->m_Stop && this->m_Tasks.empty())
                            return;

                        task = std::move(this->m_Tasks.front());
                        this->m_Tasks.pop();
                    }

                    try {
                        task();
                    }
                    catch (...) {
                        std::cout << "Task Failed!";
                    }
                }
            });
        }
    }

    void Stop() {
        {
            std::unique_lock<std::mutex> lock(this->m_QueueMutex);

            this->m_Stop = true;
        }

        this->m_Condition.notify_all();

        for (std::thread& worker : this->m_Workers)
            if (worker.joinable())
                worker.join();
    }

private:
    DynamicArray<std::thread> m_Workers;
    std::queue<VoidFunction> m_Tasks;

    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    std::atomic<b8> m_Stop;

};  // ThreadPool