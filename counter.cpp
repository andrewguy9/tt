//
//  counter.cpp
//  reqroute
//
//  Created by Andrew Thomson on 10/28/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include "counter.h"

struct counter
{
public:
    counter(double value_):value(value_) {
    }
    
    double operator()() {
        return value;
    }
private:
    double value;
};