#pragma once

#include <mutex>
#include "GnuPlotter.h"

class BaseListener {                                                                                          
    public:                                                                                                   
        virtual void update(int popSize, int duplicates)=0;                                                   
};                                                                                                            
                                                                                                              
class BirthdayParadoxListener : public BaseListener {                                                         
    public:                                                                                                   
        virtual void update(int popSize, int duplicates) {                                                    
            std::lock_guard<std::mutex> guard(m);                                                             
            gnuplotter.add(popSize, duplicates);                                                              
        }                                                                                                     
                                                                                                              
    private:                                                                                                  
        GnuPlotter gnuplotter;                                                                                
        std::mutex m;                                                                                         
};
