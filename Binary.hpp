////////////////////////////////////////////////////////////////////////////
// Binary.hpp -- 
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef __MZC3_BINARY__
#define __MZC3_BINARY__

////////////////////////////////////////////////////////////////////////////

class MBinary : public std::vector<unsigned char>
{
public:
    static const size_type npos = static_cast<size_type>(-1);
    typedef std::vector<unsigned char> super_type;
    using super_type::value_type;
    using super_type::size_type;
    using super_type::difference_type;
    using super_type::reference;
    using super_type::const_reference;
    using super_type::pointer;
    using super_type::const_pointer;
    using super_type::iterator;
    using super_type::const_iterator;
    using super_type::reverse_iterator;
    using super_type::const_reverse_iterator;
    using super_type::assign;
    using super_type::get_allocator;
    using super_type::at;
    using super_type::front;
    using super_type::back;
    using super_type::begin;
    using super_type::end;
    using super_type::rbegin;
    using super_type::rend;
    using super_type::empty;
    using super_type::size;
    using super_type::max_size;
    using super_type::reserve;
    using super_type::capacity;
    using super_type::clear;
    using super_type::insert;
    using super_type::erase;
    using super_type::push_back;
    using super_type::pop_back;
    using super_type::resize;
    using super_type::swap;
    #ifdef MODERN_CXX
        using super_type::cbegin;
        using super_type::cend;
        using super_type::crbegin;
        using super_type::crend;
        using super_type::emplace;
        using super_type::emplace_back;
    #endif

public:
    MBinary();
    MBinary(const void *pv, size_type cb);
    explicit MBinary(size_type count);
    MBinary(size_type count, const value_type& value);
    MBinary(const MBinary& bin);
    virtual ~MBinary();

    template <typename T_ITERATOR>
    MBinary(T_ITERATOR begin_, T_ITERATOR end_);

    void assign(const_pointer pb, size_type cb);

    #ifdef MODERN_CXX
        MBinary(MBinary&& bin);
        MBinary(std::initializer_list<value_type> ilist);
        void assign(std::initializer_list<value_type> ilist);
    #endif

          pointer data();
    const_pointer data() const;
          char *sz();
    const char *sz() const;
          wchar_t *wsz();
    const wchar_t *wsz() const;

    void shrink_to_fit();
    void swap(MBinary& bin);

public:
    void append(const MBinary& bin);
    void append(LPCVOID pv, size_type cb);

    template <typename T_ITERATOR>
    void append(T_ITERATOR begin_, T_ITERATOR end_);

    void appendsz(const char *psz);
    void appendsz(const char *psz, size_type cch);
    void appendsz(const wchar_t *psz);
    void appendsz(const wchar_t *psz, size_type cch);

    void addnul();

    int compare(const MBinary& bin) const;
    int compare(const void *pv2, size_type siz2) const;
    int comparesz(const char *psz) const;
    int comparesz(const wchar_t *psz) const;

    size_type find(const MBinary& bin, size_type index = 0) const;
    size_type find(const void *pv, size_type cb, size_type index = 0) const;
    size_type findsz(const char *psz, size_type cch, size_type index = 0) const;
    size_type findsz(const wchar_t *psz, size_type cch, size_type index = 0) const;

    MBinary subbin(size_type index) const;
    MBinary subbin(size_type index, size_type len) const;

    void skip(size_type len);

    MBinary left(size_type len) const;
    MBinary right(size_type len) const;
    MBinary mid(size_type index) const;
    MBinary mid(size_type index, size_type len) const;
};

bool operator==(const MBinary& bin1, const MBinary& bin2);
bool operator!=(const MBinary& bin1, const MBinary& bin2);
bool operator>=(const MBinary& bin1, const MBinary& bin2);
bool operator<=(const MBinary& bin1, const MBinary& bin2);
bool operator>(const MBinary& bin1, const MBinary& bin2);
bool operator<(const MBinary& bin1, const MBinary& bin2);

bool operator==(const MBinary& bin1, const char *psz2);
bool operator!=(const MBinary& bin1, const char *psz2);
bool operator>=(const MBinary& bin1, const char *psz2);
bool operator<=(const MBinary& bin1, const char *psz2);
bool operator>(const MBinary& bin1, const char *psz2);
bool operator<(const MBinary& bin1, const char *psz2);

bool operator==(const char *psz1, const MBinary& bin2);
bool operator!=(const char *psz1, const MBinary& bin2);
bool operator>=(const char *psz1, const MBinary& bin2);
bool operator<=(const char *psz1, const MBinary& bin2);
bool operator>(const char *psz1, const MBinary& bin2);
bool operator<(const char *psz1, const MBinary& bin2);

bool operator==(const MBinary& bin1, const wchar_t *psz2);
bool operator!=(const MBinary& bin1, const wchar_t *psz2);
bool operator>=(const MBinary& bin1, const wchar_t *psz2);
bool operator<=(const MBinary& bin1, const wchar_t *psz2);
bool operator>(const MBinary& bin1, const wchar_t *psz2);
bool operator<(const MBinary& bin1, const wchar_t *psz2);

bool operator==(const wchar_t *psz1, const MBinary& bin2);
bool operator!=(const wchar_t *psz1, const MBinary& bin2);
bool operator>=(const wchar_t *psz1, const MBinary& bin2);
bool operator<=(const wchar_t *psz1, const MBinary& bin2);
bool operator>(const wchar_t *psz1, const MBinary& bin2);
bool operator<(const wchar_t *psz1, const MBinary& bin2);

////////////////////////////////////////////////////////////////////////////

template <typename T_ITERATOR>
inline MBinary::MBinary(T_ITERATOR begin_, T_ITERATOR end_) :
    super_type(begin_, end_)
{
}

template <typename T_ITERATOR>
inline void MBinary::append(T_ITERATOR begin_, T_ITERATOR end_)
{
    insert(end(), begin_, end_);
}

////////////////////////////////////////////////////////////////////////////

namespace std
{
    void swap(MBinary& bin1, MBinary& bin2);

    #ifdef MODERN_CXX
        template <>
        struct hash<MBinary>
        {
            std::size_t operator()(const MBinary& bin) const;
        };
    #endif
} // namespace std

////////////////////////////////////////////////////////////////////////////

#ifndef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE inline
    #include "Binary_inl.hpp"
#endif

////////////////////////////////////////////////////////////////////////////

#endif  // ndef __MZC3_BINARY__
