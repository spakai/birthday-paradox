#include "ThreadPool.h"


void ThreadPool::start() {
    workThread = std::make_shared<std::thread>(&ThreadPool::worker, this);
}

void ThreadPool::worker() {
    while (!hasWork())
        ;
    pull().execute(); 
}

void ThreadPool::add(Work work) {
    workQueue.push_front(work);
}

bool ThreadPool::hasWork() {
    return !workQueue.empty();
}

Work ThreadPool::pull() {
    auto work = workQueue.back();
    workQueue.pop_back();
    return work;
}

ThreadPool::~ThreadPool() { 
    if(workThread) workThread->join();
}
