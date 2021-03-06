#pragma once

#include <mutex>
#include "GnuPlotter.h"

class BaseListener {                                                                                          
    public:                                                                                                   
        virtual void update(int popSize, int duplicates)=0;                                                   
};                                                                                                            
                                                                                                              
class BirthdayParadoxListener : public BaseListener {                                                         
    public:                                                                                                   
        void update(int popSize, int duplicates) override {                                                    
            std::lock_guard<std::mutex> guard(m);                                                             
            gnuplotter.add(popSize, duplicates);                                                              
        }                                                                                                     
                                                                                                              
    private:                                                                                                  
        GnuPlotter gnuplotter;                                                                                
        std::mutex m;                                                                                         
};
