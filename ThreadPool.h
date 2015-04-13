/***                                                                                                          
 * Excerpted from "Modern C++ Programming with Test-Driven Development",                                      
 * published by The Pragmatic Bookshelf.                                                                      
 * Copyrights apply to this code. It may not be used to create training material,                             
 * courses, books, articles, and the like. Contact us if you are in doubt.                                    
 * We make no guarantees that this code is fit for any purpose.                                               
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.                           
***/                 

#pragma once

#include <deque>
#include <thread>
#include <memory>
#include <atomic>
#include <mutex>
#include <vector>

#include "Work.h"

class ThreadPool {
    private:
        std::deque<Work> workQueue;
        std::atomic<bool> done {false};    
        std::mutex m;
        std::vector<std::shared_ptr<std::thread>> threads;
    public:
        ~ThreadPool();
        void start(unsigned int numberOfThreads);
        void worker();
        virtual void add(Work work);
        bool hasWork();
        Work pull();
};
