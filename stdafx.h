///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////

#define EXTENDS_MOBJECT /*empty*/
#define MzcFootmark()
#define MzcFootmarkThis()

////////////////////////////////////////////////////////////////////////////

template <typename T_DATA>
inline T_DATA MzcMin_(T_DATA a, T_DATA b)
{
    return (a < b ? a : b);
}

template <typename T_DATA>
inline T_DATA MzcMax_(T_DATA a, T_DATA b)
{
    return (a < b ? b : a);
}

template <typename T_DATA>
inline T_DATA MzcClamp_(T_DATA value, T_DATA min_, T_DATA max_)
{
    if (value < min_) return min_;
    if (value > max_) return max_;
    return value;
}

#define MzcMin(type,a,b) MzcMin_<type>(static_cast<type>(a), static_cast<type>(b))
#define MzcMax(type,a,b) MzcMax_<type>(static_cast<type>(a), static_cast<type>(b))
#define MzcClamp(type,value,min_,max_) \
    MzcClamp_<type>(static_cast<type>(value), \
                    static_cast<type>(min_), static_cast<type>(max_))

///////////////////////////////////////////////////////////////////////////////

#include "Binary.hpp"

///////////////////////////////////////////////////////////////////////////////
