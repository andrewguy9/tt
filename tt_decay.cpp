//
//  main.cpp
//  tt_decay
//
//  Created by Andrew Thomson on 10/30/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "top_talkers.h"
#include "top_talkers_helpers.h"
#include "counter.h"

int main(int argc, const char * argv[])
{
    if (argc < 3) {
        std::cout<<"Usage: "<<argv[0]<<" size decay_period input"<<std::endl;
        return 1;
    }
    int size = atoi(argv[1]);
    int decay = atoi(argv[2]);
    std::ifstream infile(argv[3]);
    top_talkers<std::string, counter> tt(size);
    specified_timesource ts(0.0);
    std::string conv_id;
    int timestamp;
    int last_dump = 0;
    while(infile >> conv_id >> timestamp) {
        if (last_dump + decay < timestamp) {
            last_dump = timestamp;
            std::cout << "Dump "<<timestamp <<std::endl;
            top_talkers_print<std::string, counter>(tt);
        }
        ts.set(timestamp);
        counter dc(ts, 1.0, decay);
        tt.update(conv_id, dc);
    }

    return 0;
}

