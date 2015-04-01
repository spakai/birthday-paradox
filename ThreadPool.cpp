#include "ThreadPool.h"

void ThreadPool::add(Work work) {
    workQueue.push_front(work);
}

bool ThreadPool::hasWork() {
    return !workQueue.empty();
}
