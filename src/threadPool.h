#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class threadPool
{
private:
    using Task = std::function<void()>;

    // 线程池
    std::vector<std::thread> pool;
    // 任务队列
    std::queue<Task> tasks;
    // 同步
    std::mutex m_lock;
    // 条件阻塞
    std::condition_variable cv_task;
    // 是否关闭提交
    std::atomic<bool> stoped;
    //空闲线程数量
    std::atomic<int> idlThrNum;

public:
    threadPool(unsigned short size=4);

    ~threadPool();

    int idlCount();

    template<class F, class... Args>
    auto commit(F &&f, Args &&...args) -> std::future<decltype(f(args...))> {
        if (stoped.load()) // stop == true ??
            throw std::runtime_error("commit on ThreadPool is stopped.");
        using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
        auto task = std::make_shared<std::packaged_task<RetType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        {    //对当前块的语句加锁  lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()                                         // 添加任务到队列
            std::lock_guard<std::mutex> lock{m_lock};
            // push(Task{...})
            tasks.emplace( [task]() {(*task)();});
        }
        cv_task.notify_one(); // 唤醒一个线程执行
        return future;
    }

};

#endif