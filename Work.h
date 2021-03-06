/***                                                                                                          
 * Excerpted from "Modern C++ Programming with Test-Driven Development",                                      
 * published by The Pragmatic Bookshelf.                                                                      
 * Copyrights apply to this code. It may not be used to create training material,                             
 * courses, books, articles, and the like. Contact us if you are in doubt.                                    
 * We make no guarantees that this code is fit for any purpose.                                               
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.                           
***/                 

#pragma once

#include <functional>

class Work{
    private:
        int id;
        std::function<void()> executeFunction;
    public:
        Work(int id=0)
            : id(id)
            , executeFunction([]{})
        {}
        Work(std::function<void()> executeFunction, int id=0)
            : id(id)
            , executeFunction(executeFunction)
        {} 

        int getId() const;
        void execute(); 
};
