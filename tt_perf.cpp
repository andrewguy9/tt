//
//  main.cpp
//  tt_perf
//
//  Created by Andrew Thomson on 10/28/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "top_talkers.h"
#include "top_talkers_helpers.h"

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        std::cout<<"Usage: "<<argv[0]<<" size"<<std::endl;
        return 1;
    }
    int size = atoi(argv[1]);
    top_talkers<std::string, int> tt(size);
    int w;
    std::string c;
    while(std::cin >> w >> c) {
        tt.update(c, w);
    }
    top_talkers_print<std::string, int>(tt);
    return 0;
}

