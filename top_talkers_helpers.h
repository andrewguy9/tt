#ifndef top_talkers_helpers_h
#define top_talkers_helpers_h

#include "top_talkers.h"
#include <iostream>
#include <functional>
template<typename color, typename weight>
void top_talkers_print(top_talkers<color, weight> &tt)
{
    struct {
      bool operator()(typename top_talkers<color, weight>::pair a, typename top_talkers<color, weight>::pair b)
      {
          return a.second < b.second;
      }
    } byWeight;
    auto v = tt.get();
    std::sort(v.begin(), v.end(), byWeight);
    for (auto i = v.begin(); i != v.end(); i++) {
        std::cout << i->second << " " << i->first << std::endl;
    }
}

#endif
