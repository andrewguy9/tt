#ifndef TT_LIB_H
#define TT_LIB_H

extern "C" {
    struct tt_pair
    {
        int color;
        double value;
    };

    struct tt_handle
    {
        void * ptr;
        void * ts;
    };

    int tt_init(int size, struct tt_handle * handle);
    int tt_update(int color, double delta, int time, int decay, struct tt_handle * tt);
    double tt_get_color(int color, struct tt_handle * handle);
    int tt_get(struct tt_pair * p, int size);
}

#endif
