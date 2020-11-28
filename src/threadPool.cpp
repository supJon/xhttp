//
// Created by jon on 2020/11/25.
//

#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>
#include "threadPool.h"

threadPool::threadPool(unsigned short size) : stoped{false} {
    idlThrNum = size < 1 ? 1 : size;
    for (size = 0; size < idlThrNum; ++size) { //初始化线程数量
        pool.emplace_back(
                [this] { // 工作线程函数
                    while (!this->stoped) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock{this->m_lock};
                            this->cv_task.wait(lock, [this] { return this->stoped.load() || !this->tasks.empty(); });
                            if (this->stoped && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front()); // 取一个 task
                            this->tasks.pop();
                        }
                        idlThrNum--;
                        task();
                        idlThrNum++;
                    }
                });
    }

}

    threadPool::~threadPool() {
        stoped.store(true);
        cv_task.notify_all(); // 唤醒所有线程执行
        for (std::thread &thread : pool) {
            //thread.detach(); // 让线程“自生自灭”
            if (thread.joinable())
                thread.join(); // 等待任务结束， 前提：线程一定会执行完
        }

    }

 int threadPool::idlCount() {return idlThrNum;}



