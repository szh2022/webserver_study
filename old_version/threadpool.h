#ifndef THREADPOOL_H  // 线程池
#define THREADPOOL_H

#include <pthread.h>

#include <cstdio>
#include <exception>
#include <list>

#include "lock.h"

// 线程池类，定义为模板类是为了代码复用
template <typename T>
class threadpool {
public:
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    bool append(T* request);

private:
    static void* worker(void* arg);
    void run();

private:
    int m_thread_number;        // 线程的数量
    pthread_t* m_threads;       // 线程池数组，大小为m_thread_number
    int m_max_requests;         // 请求队列中最多允许的，等待处理的数量
    std::list<T*> m_workqueue;  // 请求队列
    locker m_queuelocker;       // 互斥锁
    sem m_queuestat;            // 信号量，判断是否有任务需要处理。一开始为空，表示没有任务，阻塞。
    bool m_stop;                // 是否结束线程
};

template <typename T>
threadpool<T>::threadpool(int thread_number, int max_requests) : m_thread_number(thread_number), m_max_requests(max_requests), m_stop(false), m_threads(NULL) {
    if ((thread_number <= 0) || (max_requests <= 0))
        throw std::exception();
    m_threads = new pthread_t[m_thread_number];  // 为线程ID分配空间
    if (!m_threads) {
        throw std::exception();
    }
    // create thread_number threads,and detach it
    for (int i = 0; i < thread_number; i++) {
        printf("create the %dth thread\n", i);
        // c++ 中 worker必须是一个静态的，c中必须是全局
        // 由于worker函数中需要使用threadpool的函数。
        // 但其静态身份无法使用，故将threadpool对象本身作为参数传进入
        if (pthread_create(m_threads + i, NULL, worker, this) != 0) {
            delete[] m_threads;
            throw std::exception();
        };
        if (pthread_detach(m_threads[i]) != 0) {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template <typename T>
threadpool<T>::~threadpool() {
    delete[] m_threads;
    m_stop = true;
}

template <typename T>
bool threadpool<T>::append(T* request) {
    m_queuelocker.lock();
    if (m_workqueue.size() > m_max_requests) {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();  //信号量加一，表示请求队列中有多了一个
    return true;
}

// 线程一启动就会自动执行worker
template <typename T>
void* threadpool<T>::worker(void* arg) {
    threadpool* pool = (threadpool*)arg;
    pool->run();
    return pool;
}

template <typename T>
void threadpool<T>::run() {
    while (!m_stop) {               // 去队列中去一个任务然后做任务
        m_queuestat.wait();         // 若信号量有值，不阻塞，信号量值减一。没有值就阻塞从而判断有没有任务去做
        m_queuelocker.lock();       // 上锁
        if (m_workqueue.empty()) {  // 队列为空，则解锁等待
            m_queuelocker.unlock();
            continue;
        }
        T* request = m_workqueue.front();  // 获取第一个任务
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if (!request) {
            continue;
        }
        request->process();  // 执行任务的函数
    }
}
#endif