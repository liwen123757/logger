#include <iostream>
#include "level.hpp"
#include <assert.h>


int main()
{
    lwlog::Loglevel log;
    assert(log.to_string(lwlog::Loglevel::level::INFO));
    std::cout<<"test success"<<std::endl;
    return 0;
}