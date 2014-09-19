MZC_INLINE MBinary::MBinary()
{
}

MZC_INLINE MBinary::MBinary(const void *pv, size_type cb) :
    super_type(
        reinterpret_cast<const unsigned char *>(pv),
        reinterpret_cast<const unsigned char *>(pv) + cb)
{
}

MZC_INLINE /*explicit*/ MBinary::MBinary(size_type count) :
    super_type(count)
{
}

MZC_INLINE
MBinary::MBinary(size_type count, const value_type& value) :
    super_type(count, value)
{
}

MZC_INLINE MBinary::MBinary(const MBinary& bin) :
    super_type(bin)
{
}

MZC_INLINE /*virtual*/ MBinary::~MBinary()
{
}

#ifdef MODERN_CXX
    MZC_INLINE MBinary::MBinary(MBinary&& bin) : super_type(bin)
    {
    }

    MZC_INLINE MBinary::MBinary(std::initializer_list<value_type> ilist) :
        super_type(ilist)
    {
    }
#endif

MZC_INLINE MBinary::pointer MBinary::data()
{
    return &(*this)[0];
}

MZC_INLINE MBinary::const_pointer MBinary::data() const
{
    return &(*this)[0];
}

MZC_INLINE char *MBinary::sz()
{
    return reinterpret_cast<char *>(data());
}

MZC_INLINE const char *MBinary::sz() const
{
    return reinterpret_cast<const char *>(data());
}

MZC_INLINE wchar_t *MBinary::wsz()
{
    return reinterpret_cast<wchar_t *>(data());
}

MZC_INLINE const wchar_t *MBinary::wsz() const
{
    return reinterpret_cast<const wchar_t *>(data());
}

MZC_INLINE void MBinary::shrink_to_fit()
{
    #ifdef MODERN_CXX
        super_type::shrink_to_fit();
    #else
        super_type(begin(), end()).swap(*this);
    #endif
}

MZC_INLINE void MBinary::append(LPCVOID pv, size_type cb)
{
    assert(pv || !cb);
    const_pointer pb = reinterpret_cast<const_pointer>(pv);
    super_type::insert(end(), pb, pb + cb);
}

MZC_INLINE void MBinary::appendsz(const char *psz)
{
    assert(psz);
    using namespace std;
    append(psz, strlen(psz) * sizeof(CHAR));
}

MZC_INLINE void MBinary::appendsz(const wchar_t *psz)
{
    assert(psz);
    using namespace std;
    append(psz, wcslen(psz) * sizeof(WCHAR));
}

MZC_INLINE void MBinary::appendsz(const char *psz, size_type cch)
{
    assert(psz);
    append(psz, cch * sizeof(CHAR));
}

MZC_INLINE void MBinary::appendsz(const wchar_t *psz, size_type cch)
{
    assert(psz);
    append(psz, cch * sizeof(WCHAR));
}

MZC_INLINE void MBinary::append(const MBinary& bin)
{
    append(bin.data(), bin.size());
}

MZC_INLINE void MBinary::addnul()
{
    push_back(0);
}

MZC_INLINE int MBinary::compare(const MBinary& bin) const
{
    return compare(bin.data(), bin.size());
}

MZC_INLINE int MBinary::comparesz(const char *psz) const
{
    assert(psz);
    using namespace std;
    return compare(psz, strlen(psz) * sizeof(char));
}

MZC_INLINE int MBinary::comparesz(const wchar_t *psz) const
{
    assert(psz);
    using namespace std;
    return compare(psz, wcslen(psz) * sizeof(WCHAR));
}

MZC_INLINE void MBinary::skip(size_type len)
{
    erase(begin(), begin() + len);
}

MZC_INLINE MBinary::size_type
MBinary::find(const MBinary& bin, size_type index/* = 0*/) const
{
    return find(bin.data(), bin.size(), index);
}

MZC_INLINE MBinary::size_type
MBinary::findsz(const char *psz, size_type cch, size_type index/* = 0*/) const
{
    using namespace std;
    return find(reinterpret_cast<const_pointer>(psz),
                strlen(psz) * sizeof(CHAR), index);
}

MZC_INLINE MBinary::size_type
MBinary::findsz(const wchar_t *psz, size_type cch, size_type index/* = 0*/) const
{
    using namespace std;
    return find(reinterpret_cast<const_pointer>(psz),
                wcslen(psz) * sizeof(WCHAR), index);
}

MZC_INLINE void MBinary::assign(const_pointer pb, size_type cb)
{
    assert(pb || !cb);
    super_type::assign(pb, pb + cb);
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE bool operator==(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) == 0;
}

MZC_INLINE bool operator!=(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) != 0;
}

MZC_INLINE bool operator>=(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) >= 0;
}

MZC_INLINE bool operator<=(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) <= 0;
}

MZC_INLINE bool operator>(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) > 0;
}

MZC_INLINE bool operator<(const MBinary& bin1, const MBinary& bin2)
{
    return bin1.compare(bin2) < 0;
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE bool operator==(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) == 0;
}

MZC_INLINE bool operator!=(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) != 0;
}

MZC_INLINE bool operator>=(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) >= 0;
}

MZC_INLINE bool operator<=(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) <= 0;
}

MZC_INLINE bool operator>(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) > 0;
}

MZC_INLINE bool operator<(const MBinary& bin1, const char *psz2)
{
    return bin1.comparesz(psz2) < 0;
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE bool operator==(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) == 0;
}

MZC_INLINE bool operator!=(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) != 0;
}

MZC_INLINE bool operator>=(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) >= 0;
}

MZC_INLINE bool operator<=(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) <= 0;
}

MZC_INLINE bool operator>(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) > 0;
}

MZC_INLINE bool operator<(const char *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) < 0;
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE bool operator==(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) == 0;
}

MZC_INLINE bool operator!=(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) != 0;
}

MZC_INLINE bool operator>=(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) >= 0;
}

MZC_INLINE bool operator<=(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) <= 0;
}

MZC_INLINE bool operator>(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) > 0;
}

MZC_INLINE bool operator<(const MBinary& bin1, const wchar_t *psz2)
{
    return bin1.comparesz(psz2) < 0;
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE bool operator==(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) == 0;
}

MZC_INLINE bool operator!=(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) != 0;
}

MZC_INLINE bool operator>=(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) >= 0;
}

MZC_INLINE bool operator<=(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) <= 0;
}

MZC_INLINE bool operator>(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) > 0;
}

MZC_INLINE bool operator<(const wchar_t *psz1, const MBinary& bin2)
{
    return -bin2.comparesz(psz1) < 0;
}

////////////////////////////////////////////////////////////////////////////

MZC_INLINE void std::swap(MBinary& bin1, MBinary& bin2)
{
    bin1.swap(bin2);
}

////////////////////////////////////////////////////////////////////////////
