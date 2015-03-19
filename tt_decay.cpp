//
//  main.cpp
//  tt_decay
//
//  Created by Andrew Thomson on 10/30/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "top_talkers.h"
#include "counter.h"

typedef top_talkers<int, counter> tt_type;

int main(int argc, const char * argv[])
{
    if (argc < 3) {
        std::cout<<"Usage: "<<argv[0]<<" size decay_period input"<<std::endl;
        return 1;
    }
    int size = atoi(argv[1]);
    int decay = atoi(argv[2]);
    std::ifstream infile(argv[3]);
    tt_type tt(size);
    specified_timesource ts(0.0);
    int conv_id;
    int timestamp;
    int last_dump = 0;
    while(infile >> conv_id >> timestamp) {
        if (last_dump + decay < timestamp) {
            last_dump = timestamp;
            std::cout << "Dump "<<timestamp <<std::endl;
            top_talkers_print<int, counter>(tt);
        }
        ts.set(timestamp);
        counter dc(ts, 1.0, decay);
        tt.update(conv_id, dc);
    }

    return 0;
}

