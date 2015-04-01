#include "ThreadPool.h"

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
