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
#include "Work.h"

class ThreadPool {
    private:
        std::deque<Work> workQueue;
        std::shared_ptr<std::thread> workThread;
        std::atomic<bool> done {false};    
        std::mutex m ;
    public:
        ~ThreadPool();
        void start();
        void worker();
        void add(Work work);
        bool hasWork();
        Work pull();
};
