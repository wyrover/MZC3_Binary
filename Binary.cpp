#include "stdafx.h"

#ifdef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE  /*empty*/
    #include "Binary_inl.h"
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////

int MBinary::compare(const void *pv2, size_type siz2) const
{
    assert(pv2 || siz2);
    const_pointer pb = data();
    const_pointer pb2 = reinterpret_cast<const_pointer>(pv2);
    size_type siz1 = size();
    size_type siz = MzcMin(size_type, siz1, siz2);
    for (size_type i = 0; i < siz; i++)
    {
        if (pb[i] < pb2[i])
            return -1;
        if (pb[i] > pb2[i])
            return 1;
    }
    if (siz1 < siz2)
        return -1;
    if (siz1 > siz2)
        return 1;
    return 0;
}

MBinary::size_type
MBinary::find(const void *pv, size_type cb, size_type index/* = 0*/) const
{
    const_pointer pb2 = reinterpret_cast<const_pointer>(pv);
    const size_type siz1 = size(), siz2 = cb;
    if (siz1 < siz2)
        return npos;

    const_pointer pb1 = data();
    for (size_type i = index; i < siz1 - siz2; i++)
    {
        using namespace std;
        if (memcmp(pb1 + i, pb2 + i, siz2) == 0)
            return i;
    }
    return npos;
}

MBinary MBinary::subbin(size_type index) const
{
    assert(index < size());
    return subbin(index, size() - index);
}

MBinary MBinary::subbin(size_type index, size_type len) const
{
    assert(index < size());
    assert(index + len <= size());
    const_iterator it = begin() + index;
    return MBinary(it, it + len);
}

MBinary MBinary::left(size_type len) const
{
    return subbin(0, len);
}

MBinary MBinary::right(size_type len) const
{
    return subbin(size() - len, len);
}

MBinary MBinary::mid(size_type index) const
{
    return subbin(index);
}

MBinary MBinary::mid(size_type index, size_type len) const
{
    return subbin(index, len);
}

////////////////////////////////////////////////////////////////////////////

#ifdef MODERN_CXX
    std::size_t std::hash<MBinary>::operator()(const MBinary& bin) const
    {
        #ifdef _WIN64
            std::size_t code = 0xA2B4FCDE9F1C2ECA;
        #else
            std::size_t code = 0xA2B4FCDE;
        #endif
        std::size_t i, c = bin.size();
        code ^= c;
        for (i = 0; i < c; i++)
        {
            code ^= bin[i];
            code <<= 2;
        }
        return code;
    }
#endif  // def MODERN_CXX

////////////////////////////////////////////////////////////////////////////

#ifdef UNITTEST
    // unit test and example
    #include <cstdio>
    using namespace std;
    int main(void)
    {
        MBinary bin;
        bin.appendsz("TEST");
        printf("%u: %.*s\n", int(bin.size()), int(bin.size()), bin.sz());
        bin.appendsz("test");
        printf("%u: %.*s\n", int(bin.size()), int(bin.size()), bin.sz());
        bin.skip(4);
        printf("%u: %.*s\n", int(bin.size()), int(bin.size()), bin.sz());
        MBinary bin2("ABC", 3);
        printf("%u: %.*s\n", int(bin2.size()), int(bin2.size()), bin2.sz());
        bin.append(bin2);
        printf("%u: %.*s\n", int(bin.size()), int(bin.size()), bin.sz());
        bin.skip(5);
        printf("%u: %.*s\n", int(bin.size()), int(bin.size()), bin.sz());
        return 0;
    }
#endif
