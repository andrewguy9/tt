//
//  counter.h
//  reqroute
//
//  Created by Andrew Thomson on 10/28/13.
//  Copyright (c) 2013 Andrew Thomson. All rights reserved.
//

#ifndef _LIBCPP_COUNTER
#define _LIBCPP_COUNTER

#include <__config>
#include <type_traits>
#include <stdexcept>
#include <cmath>
#include <sstream>
#if defined(_LIBCPP_NO_EXCEPTIONS)
#include <cassert>
#endif

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

class timesource
{
public:
    
    virtual void set(double t_) = 0;
    virtual double get() const = 0;
};

class specified_timesource: public timesource
{
private:
    double time;
public:
    specified_timesource(double t_): time(t_) { }
    void set(double t_) {time = t_;}
    double get() const {return time;}
};

class counter
{
public:
    typedef double value_type;
private:
    value_type value;
    timesource & ts;
    double period;
    double last_time;
public:
    counter(timesource & _ts, const value_type& _value = value_type(), value_type _p=60) : value(_value), ts(_ts), period(_p), last_time(ts.get()) {}
    counter(const counter& __c) : value(__c.get()), period(__c.period), ts(__c.ts), last_time(__c.last_time) {}
    
    value_type get() const {
        double delta = ts.get() - last_time;
        double alpha = exp(-delta/period);
        return alpha * value;
    }

    counter& set(value_type __value) {
        value = __value;
        last_time = ts.get();
    }
    //TODO BAD....
    counter copy() const {
        return *this;
    }
    //TODO END BAD....
    
    counter& operator= (const value_type& rhs) {return set(      rhs);}
    counter& operator+=(const value_type& rhs) {return set(get()+rhs);}
    
    counter& operator= (const counter& rhs) {return set(      rhs.get());}
    counter& operator+=(const counter& rhs) {return set(get()+rhs.get());}
    counter& operator++()                   {return set(get()+1.0);}
    
    counter& operator++(int unused) {counter t = copy(); set(get()+1.0); return t;}
};

counter operator+(const counter& lhs, const counter& rhs)
{
    counter tmp = lhs.copy();
    tmp += rhs;
    return tmp;
}

template<class Tp>
counter operator+(const counter& lhs, const Tp& rhs)
{
    counter tmp = lhs.copy();
    tmp += rhs;
    return tmp;
}

template<class Tp>
counter operator+(const Tp& lhs, const counter& rhs)
{
    counter tmp = lhs.copy();
    tmp += rhs;
    return tmp;
}
counter operator+(const counter& lhs)
{
    return lhs;
}

bool operator==(const counter& lhs, const counter& rhs)
{
    return lhs.get() == rhs.get();
}

template<class Tp>
bool operator==(const counter& lhs, const Tp& rhs)
{
    return lhs.get() == rhs;
}

template<class Tp>
bool operator==(const Tp& lhs, const counter& rhs)
{
    return lhs == rhs.get();
}

bool operator!=(const counter& lhs, const counter& rhs)
{
    return !(lhs == rhs);
}

template<class Tp>
bool operator!=(const counter& lhs, const Tp& rhs)
{
    return !(lhs == rhs);
}

template<class Tp>
bool operator!=(const Tp& lhs, const counter& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const counter& lhs, const counter& rhs)
{
    return lhs.get() < rhs.get();
}

template<class Tp>
bool operator<(const counter& lhs, const Tp& rhs)
{
    return lhs < rhs.get();
}

template<class Tp>
bool operator<(const Tp& lhs, const counter& rhs)
{
    return lhs.get() < rhs;
}

/*
template<class _CharT, class _Traits>
std::basic_istream<_CharT, _Traits>&
operator>>(std::basic_istream<_CharT, _Traits>& __is, counter& __x)
{
    if (__is.good())
    {
        ws(__is);
        if (__is.peek() == _CharT('('))
        {
            __is.get();
            double __r;
            __is >> __r;
            if (!__is.fail())
            {
                ws(__is);
                _CharT __c = __is.peek();
                if (__c == _CharT(','))
                {
                    __is.get();
                    double __i;
                    __is >> __i;
                    if (!__is.fail())
                    {
                        ws(__is);
                        __c = __is.peek();
                        if (__c == _CharT(')'))
                        {
                            __is.get();
                            __x = counter(__r, __i);
                        }
                        else
                            __is.setstate(ios_base::failbit);
                    }
                    else
                        __is.setstate(ios_base::failbit);
                }
                else if (__c == _CharT(')'))
                {
                    __is.get();
                    __x = counter(__r, double(0));
                }
                else
                    __is.setstate(ios_base::failbit);
            }
            else
                __is.setstate(ios_base::failbit);
        }
        else
        {
            double __r;
            __is >> __r;
            if (!__is.fail())
                __x = counter(__r);
            else
                __is.setstate(ios_base::failbit);
        }
    }
    else
        __is.setstate(ios_base::failbit);
    return __is;
}
*/

template<class _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os, const counter& __x)
{
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    __s << __x.get();
    return __os << __s.str();
}

#endif  // _LIBCPP_COUNTER

