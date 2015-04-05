#include "ThreadPool.h"


void ThreadPool::start() {
    workThread = std::make_shared<std::thread>(&ThreadPool::worker, this);
}

void ThreadPool::worker() {
    while (!done) {
        while (!done && !hasWork())
            ;
        if(done) break;
        pull().execute(); 
    }
}

void ThreadPool::add(Work work) {
    std::lock_guard<std::mutex> guard(m); 
    workQueue.push_front(work);
}

bool ThreadPool::hasWork() {
    std::lock_guard<std::mutex> guard(m); 
    return !workQueue.empty();
}

Work ThreadPool::pull() {
    std::lock_guard<std::mutex> guard(m); 
    auto work = workQueue.back();
    workQueue.pop_back();
    return work;
}

ThreadPool::~ThreadPool() {
    done = true; 
    if(workThread) workThread->join();
}
