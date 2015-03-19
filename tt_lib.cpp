//
//  main.cpp
//  tt_decay
//
//  Created by Andrew Thomson on 10/30/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#include "tt_lib.h"
#include "top_talkers.h"
#include "counter.h"

#include <algorithm>

typedef top_talkers<int, counter> tt_type;

int tt_init(int size, struct tt_handle * handle)
{
    try {
        tt_type * tt = new tt_type(size);
        handle->ptr = tt;
        specified_timesource * ts = new specified_timesource(0.0);
        handle->ts = ts;
        return 1;
    } catch (std::bad_alloc&) {
        return -1;
    } catch (...) {
        return -2;
    }
}

int tt_update(int color, double delta, int time, double decay, struct tt_handle * handle)
{
    try {
        specified_timesource * ts = (specified_timesource *) handle->ts;
        ts->set(time);
        counter dc(*ts, 1.0, decay);
        tt_type * tt = (tt_type *) handle->ptr;
        tt->update(color, dc);
        return 1;
    } catch (...) {
        return -1;
    }
}

double tt_get_color(int color, struct tt_handle * handle)
{
    tt_type * tt = (tt_type *) handle->ptr;
    return tt->get(color).get();
}

int tt_get(struct tt_pair * pairs, size_t size, struct tt_handle * handle)
{
    try {
        int i= 0;
        tt_type * tt = (tt_type *) handle->ptr;
        std::vector<tt_type::pair> top = tt->get();
        for (i = 0;
                i < std::min<size_t>(size, top.size());
                i++)
        {
            tt_type::pair p = top[i];
            pairs[i].color = p.first;
            pairs[i].value = p.second.get();
        }
        return i;
    } catch (...) {
        return -1;
    }
}
