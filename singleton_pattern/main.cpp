#include <iostream>
#include <mutex>
#include <atomic>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

/**
 * 单例模式
 */
#if 0
// 饿汉模式
class TaskQueue {
public:
    TaskQueue(TaskQueue& t) = delete;
    TaskQueue(TaskQueue&& t) = delete;

    static TaskQueue* getInstance() {
        return task;
    }

    void print() {
        cout << "我是一个单例模式的函数..." << endl;
    }
private:
    TaskQueue() = default;
    static TaskQueue* task;
};
TaskQueue* TaskQueue::task = new TaskQueue();   // 初始化时直接赋值
#endif

#if 0
// 懒汉模式
class TaskQueue {
public:
    TaskQueue(TaskQueue& t) = delete;
    TaskQueue(TaskQueue&& t) = delete;

    static TaskQueue* getInstance() {
        static TaskQueue task;
        return &task;
    }

    void print() {
        cout << "我是一个单例模式的函数..." << endl;
    }
private:
    TaskQueue() = default;
    static atomic<TaskQueue*> task_;
    static mutex mtx_;
};
#endif

#if 1
// 基于单例模式的任务队列
class TaskQueue {
public:
    TaskQueue(TaskQueue& t) = delete;
    TaskQueue(TaskQueue&& t) = delete;

    static TaskQueue* getInstance() {
        return task_;
    }

    // 添加任务
    void addTask(int node) {
        lock_guard<mutex> locker(mtx_);
        que_.push(node);
    }

    // 删除任务
    bool popTask() {
        lock_guard<mutex> locker(mtx_);
        if (que_.empty()) {
            return false;
        }
        que_.pop();
        return true;
    }

    // 当前任务的个数
    int taskNum() {
        lock_guard<mutex> locker(mtx_);
        if (que_.empty()) {
            return -1;
        }
        return que_.size();
    }

    // 取出一个任务（不删除）
    int takeTask() {
        lock_guard<mutex> locker(mtx_);
        if (que_.empty()) {
            return -1;
        }
        return que_.front();
    }

    // 判断是否为空
    bool isEmpty() {
        lock_guard<mutex> locker(mtx_);
        return que_.empty();
    }

private:
    TaskQueue() = default;
    static TaskQueue* task_;
    queue<int> que_;
    mutex mtx_; // 多线程时保护任务队列
};
TaskQueue* TaskQueue::task_ = new TaskQueue();   // 初始化时直接赋值
#endif

int main() {
    TaskQueue* taskQ = TaskQueue::getInstance();
    // 生产者
    thread t1([=]() {
        for (int i = 0; i < 10; i++) {
            taskQ->addTask(i + 10);
            cout << "+++ push data: " << i + 10 << ", threadID: " << this_thread::get_id() << endl;

            this_thread::sleep_for(chrono::microseconds(500));
        }
    });

    // 消费者
    thread t2([=]() {
        this_thread::sleep_for(chrono::microseconds(100));  // 为了让消费者工作慢一点

        while (!taskQ->isEmpty()) {
            int num = taskQ->takeTask();
            cout << "+++ take data: " << num << ", threadID: " << this_thread::get_id() << endl;
            taskQ->popTask();

            this_thread::sleep_for(chrono::microseconds(1000)); // 为了让消费者消费慢一点
        }
    });

    t1.join();
    t2.join();

    return 0;
}
