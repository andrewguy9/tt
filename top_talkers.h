//
//  top_talkers.h
//  reqroute
//
//  Created by Andrew Thomson on 10/28/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#ifndef reqroute_top_talkers_h
#define reqroute_top_talkers_h

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

template<typename color_, typename weight_>
class top_talkers
{
public:
    typedef color_ color;
    typedef weight_ weight;
    typedef std::pair<color, weight> pair;

    top_talkers(size_t size);
    ~top_talkers();
    void update(color, weight);
    weight get(color) const;
    std::vector<pair> get() const;

private:
    struct heap_comparator
    {
        double operator()(pair const & lhs, pair const & rhs) const
        {
            return !(lhs.second < rhs.second);
        }
    };
    typedef boost::heap::fibonacci_heap<pair, boost::heap::compare<heap_comparator> > weight_heap;
    typedef typename weight_heap::handle_type weight_handle;
    typedef boost::unordered_map<color, weight_handle> color_map;

    size_t size;
    weight_heap weights;
    color_map colors;
};

template<typename color, typename weight>
top_talkers<color, weight>::top_talkers(size_t capacity):
size(capacity),
weights(),
colors()
{
}

template<typename color, typename weight>
top_talkers<color, weight>::~top_talkers()
{
}

template<typename color, typename weight>
weight top_talkers<color, weight>::get(color c) const
{
    auto ci = colors.find(c);
    if (ci != colors.end()) {
        auto wh = (*ci).second;
        return (*wh).second;
    } else {
        auto wh = weights.top();
        return wh.second;
    }
}

template<typename color, typename weight>
void top_talkers<color, weight>::update(color c, weight w)
{
    if (colors.find(c) == colors.end()) {
        size_t cur_size = weights.size();
        if (cur_size < size) {
            pair p(c,w);
            auto wh = weights.push(p);
            colors[c] = wh;
        } else {
            pair p = weights.top();
            weights.pop();
            colors.erase(p.first);
            p.first = c;
            p.second += w;
            auto wh = weights.push(p);
            colors[c] = wh;
        }
    } else {
        auto wh = colors[c];
        (*wh).second += w;
        weights.update(wh);
    }
}

template<typename color, typename weight>
std::vector<std::pair<color, weight>> top_talkers<color, weight>::get() const
{
    std::vector<pair> out;
    for (auto i = colors.begin();
         i != colors.end();
         i++){
        auto wh = (*i).second;
        pair p = (*wh);
        out.push_back(p);
    }
    return out;
}

#endif
