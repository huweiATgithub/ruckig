#pragma once

#ifdef TC_VER

#include "TcMath.h"
#define compat_sqrt sqrt_
#define compat_abs fabs_
#define compat_sin sin_
#define compat_cos cos_
#define compat_tan tan_
#define compat_asin asin_
#define compat_acos acos_
#define compat_atan atan_
#define compat_cbrt cbrt_
#define compat_fmod fmod_

namespace std {
inline int isnan(const double &x){ return isnan_(x);};
inline bool isfinite(double arg)
{
    return(TcMath::finite_(arg) != 0);
}

inline bool isfinite(long double arg)
{
    return(TcMath::finite_(arg) != 0);
}

inline bool isinf(float arg)
{
#ifdef TCSTL11
    static_assert(sizeof(float) == 4,
        "This implementation of isinf requires 32 bit floats.");
#endif
    unsigned __int32* p = (unsigned __int32*)&arg;

    return (p[0] & 0x7FFFFFFF) == 0x7F800000;
}

inline bool isinf(double arg)
{
#ifdef TCSTL11
    static_assert(sizeof(double) == 8,
        "This implementation of isinf requires 64 bit doubles.");
#endif
    unsigned __int32* p = (unsigned __int32*)&arg;

    return ((p[1] & 0x7FFFFFFF) == 0x7FF00000) && (p[0] == 0);
}

inline bool isinf(long double arg)
{
#ifdef TCSTL11
    static_assert(sizeof(long double) == 8,
        "This implementation of isinf requires 64 bit long doubles.");
#endif
    unsigned __int32* p = (unsigned __int32*)&arg;

    return ((p[1] & 0x7FFFFFFF) == 0x7FF00000) && (p[0] == 0);
}

typedef struct _ldiv_t
{
    long quot;
    long rem;
} ldiv_t;

inline ldiv_t div(long const _A1, long const _A2) throw()
{
    // TODO: implement me
    return {};
}

// implementation of std::iota
template <class _FwdIt, class _Ty>
inline void iota(_FwdIt _First, _FwdIt _Last, _Ty _Val) {
    // compute increasing sequence into [_First, _Last)
    //_Adl_verify_range(_First, _Last);
     auto _UFirst      = (_First);
     const auto _ULast = (_Last);
     for (; _UFirst != _ULast; ++_UFirst, (void) ++_Val) {
         *_UFirst = _Val;
     }
}

} // namespace std

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

#else

#define compat_sqrt std::sqrt
#define compat_abs std::abs
#define compat_sin std::sin
#define compat_cos std::cos
#define compat_tan std::tan
#define compat_asin std::asin
#define compat_acos std::acos
#define compat_atan std::atan
#define compat_cbrt std::cbrt
#define compat_fmod std::fmod

#endif
namespace math_compat
{
}
