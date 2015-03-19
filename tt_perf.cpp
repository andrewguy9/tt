//
//  main.cpp
//  tt_perf
//
//  Created by Andrew Thomson on 10/28/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "top_talkers.h"

typedef top_talkers<int, int> tt_type;

int main(int argc, const char * argv[])
{
    if (argc < 2) {
        std::cout<<"Usage: "<<argv[0]<<" size input"<<std::endl;
        return 1;
    }
    int size = atoi(argv[1]);
    std::ifstream infile(argv[2]);
    tt_type tt(size);
    tt_type::color c;
    tt_type::weight w;
    while(infile >> c >> w) {
        tt.update(c, w);
    }
    top_talkers_print<int, int>(tt);
    return 0;
}

