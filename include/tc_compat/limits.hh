////////////////////////////////////////////////////////////////////////////////
// This is copied from <limits> from the Beckhoff TwinCAT Software Development Kit.
// Modifications are: `#include <cmath>` is deleted
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
// limits standard header
#pragma once

#ifndef _TC_LIMITS_
#define _TC_LIMITS_

#ifndef DISABLE_TWINCAT_STL

#include <Stl/Stl/TcStlCommon.h>
#include <Stl/Stl/TcStlUtility.h>

#if TC_STL_IN_NAMESPACE_STD
	#define TC_LIMITS_NAMESPACE std
	#include "limits.h"
#else
	#define TC_LIMITS_NAMESPACE tc_std
	#include "limits.h"
	#include "tc_cmath.h"
#endif

#ifndef WCHAR_MIN
	#define WCHAR_MIN 0x0000
#endif

#ifndef WCHAR_MAX
	#define WCHAR_MAX 0xffff
#endif


#ifndef TCSTL11
#ifndef DBL_DECIMAL_DIG
#define DBL_DECIMAL_DIG 17
#endif
#ifndef FLT_DECIMAL_DIG
#define FLT_DECIMAL_DIG 9
#endif
#ifndef DBL_TRUE_MIN
#define DBL_TRUE_MIN 4.9406564584124654e-324
#endif
#ifndef FLT_TRUE_MIN
#define FLT_TRUE_MIN 1.401298464e-45F
#endif
#endif

#define __TC_LIMITS_LOG10_2_VALUE 0.30102999566398119521373889472449

namespace TC_LIMITS_NAMESPACE
{

	typedef enum
	{	// constants for different IEEE float denormalization styles
		denorm_indeterminate = -1,
		denorm_absent = 0,
		denorm_present = 1
	}
	float_denorm_style;

	// ENUM float_round_style
	typedef enum
	{	// constants for different IEEE rounding styles
		round_indeterminate = -1,
		round_toward_zero = 0,
		round_to_nearest = 1,
		round_toward_infinity = 2,
		round_toward_neg_infinity = 3
	}
	float_round_style;

	///////////////////////////////////////////////////////////////////////////////
	// numeric_limits
	///////////////////////////////////////////////////////////////////////////////

	namespace limitsHelper
	{
		class numerical_limits_base
		{
		public:
			static TCSTL_CONSTEXPR_VAR int digits = 0;
			static TCSTL_CONSTEXPR_VAR int digits10 = 0;
			static TCSTL_CONSTEXPR_VAR int max_digits10 = 0;
			static TCSTL_CONSTEXPR_VAR bool is_signed = false;
			static TCSTL_CONSTEXPR_VAR bool is_integer = false;
			static TCSTL_CONSTEXPR_VAR bool is_exact = false;
			static TCSTL_CONSTEXPR_VAR int radix = 0;
			static TCSTL_CONSTEXPR_VAR int min_exponent = 0;
			static TCSTL_CONSTEXPR_VAR int min_exponent10 = 0;
			static TCSTL_CONSTEXPR_VAR int max_exponent = 0;
			static TCSTL_CONSTEXPR_VAR int max_exponent10 = 0;
			static TCSTL_CONSTEXPR_VAR bool has_infinity = false;
			static TCSTL_CONSTEXPR_VAR bool has_quiet_NaN = false;
			static TCSTL_CONSTEXPR_VAR bool has_signaling_NaN = false;
			static TCSTL_CONSTEXPR_VAR float_denorm_style has_denorm = denorm_absent;
			static TCSTL_CONSTEXPR_VAR bool has_denorm_loss = false;
			static TCSTL_CONSTEXPR_VAR bool is_iec559 = false;
			static TCSTL_CONSTEXPR_VAR bool is_bounded = false;
			static TCSTL_CONSTEXPR_VAR bool is_modulo = false;
			static TCSTL_CONSTEXPR_VAR bool traps = false;
			static TCSTL_CONSTEXPR_VAR bool tinyness_before = false;
			static TCSTL_CONSTEXPR_VAR float_round_style round_style = round_toward_zero;
		};

#ifndef TCSTL11
		union _hexlimits_single__
		{
			const unsigned long hexval;
			const float floatval;
		};
		union _hexlimits_double__
		{
			const unsigned long long hexval;
			const double doubleval;
			const long double ldoubleval;
		};

		static const _hexlimits_single__ __qNanLimitflt = { 0x7FC00000UL };
		static const _hexlimits_single__ __sNanLimitflt = { 0x7FC00001UL };
		static const _hexlimits_single__ __infLimitflt =  { 0x7F800000UL };

		static const _hexlimits_double__ __qNanLimitdbl = { 0x7FF8000000000000ULL };
		static const _hexlimits_double__ __sNanLimitdbl = { 0x7FF8000000000001ULL };
		static const _hexlimits_double__ __infLimitdbl =  { 0x7FF0000000000000ULL };
#endif // !TCSTL11

		class _integer_numerical_limits: public numerical_limits_base
		{
		public:
			static TCSTL_CONSTEXPR_VAR bool is_specialized = true;
			static TCSTL_CONSTEXPR_VAR bool is_integer = true;
			static TCSTL_CONSTEXPR_VAR bool is_exact = true;
			static TCSTL_CONSTEXPR_VAR bool is_bounded = true;
			static TCSTL_CONSTEXPR_VAR int radix = 2;
			static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		};

		class _floatingpoint_numerical_limits: public numerical_limits_base
		{
		public:
			static TCSTL_CONSTEXPR_VAR bool is_specialized = true;
			static TCSTL_CONSTEXPR_VAR bool has_infinity = true;
			static TCSTL_CONSTEXPR_VAR bool has_quiet_NaN = true;
			static TCSTL_CONSTEXPR_VAR bool has_signaling_NaN = true;
			static TCSTL_CONSTEXPR_VAR bool is_iec559 = true;
			static TCSTL_CONSTEXPR_VAR bool is_signed = true;
			static TCSTL_CONSTEXPR_VAR float_denorm_style has_denorm = float_denorm_style::denorm_present;
			static TCSTL_CONSTEXPR_VAR int has_denorm_loss = true;
			static TCSTL_CONSTEXPR_VAR bool is_bounded = true;
			static TCSTL_CONSTEXPR_VAR float_round_style round_style = round_to_nearest;
		};
	}

	template<typename _Ty> class numeric_limits : public limitsHelper::numerical_limits_base
	{
	public:
		static TCSTL_CONSTEXPR_VAR bool is_specialized = false;
#ifdef TCSTL11
		static TCSTL_CONSTEXPR_FUNC _Ty min() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty max() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty lowest() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty epsilon() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty round_error() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty infinity() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty quiet_NaN() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty signaling_NaN() TCSTL_NOEXCEPT { return _Ty(); };
		static TCSTL_CONSTEXPR_FUNC _Ty denorm_min() TCSTL_NOEXCEPT { return _Ty(); };
#else
		static TCSTL_CONSTEXPR_FUNC _Ty min() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty max() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty epsilon() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty round_error() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty infinity() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty quiet_NaN() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty signaling_NaN() throw();
		static TCSTL_CONSTEXPR_FUNC _Ty denorm_min() throw();
#endif
	};

	// redirect types with modifier const, volatile, or const volatile to numeric_limits without modifier
	template<class _Ty> class numeric_limits<const _Ty> : public numeric_limits<_Ty> {};
	template<class _Ty> class numeric_limits<volatile _Ty> : public numeric_limits<_Ty> {};
	template<class _Ty> class numeric_limits<const volatile _Ty> : public numeric_limits<_Ty> {};

	template<> class numeric_limits<bool>:
		public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC bool min() TCSTL_NOEXCEPT { return false; };
		static TCSTL_CONSTEXPR_FUNC bool max() TCSTL_NOEXCEPT { return true; };
		static TCSTL_CONSTEXPR_FUNC bool lowest() TCSTL_NOEXCEPT { return min(); };
		static TCSTL_CONSTEXPR_FUNC bool epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC bool round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC bool infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC bool quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC bool signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC bool denorm_min() TCSTL_NOEXCEPT { return false; };

		static TCSTL_CONSTEXPR_VAR int digits = 1;
		static TCSTL_CONSTEXPR_VAR bool traps = false;
		static TCSTL_CONSTEXPR_VAR bool is_signed = false;
		static TCSTL_CONSTEXPR_VAR bool is_modulo = false;
	};

	template<> class numeric_limits<char>: public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC char max() TCSTL_NOEXCEPT { return CHAR_MAX; };
		static TCSTL_CONSTEXPR_FUNC char min() TCSTL_NOEXCEPT { return CHAR_MIN; };
		static TCSTL_CONSTEXPR_FUNC char lowest() TCSTL_NOEXCEPT { return CHAR_MIN; };
		static TCSTL_CONSTEXPR_FUNC char epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = (CHAR_MIN == SCHAR_MIN);
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT - is_signed;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<signed char>:  public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC signed char max() TCSTL_NOEXCEPT { return SCHAR_MAX; };
		static TCSTL_CONSTEXPR_FUNC signed char min() TCSTL_NOEXCEPT { return SCHAR_MIN; };
		static TCSTL_CONSTEXPR_FUNC signed char lowest() TCSTL_NOEXCEPT { return SCHAR_MIN; };
		static TCSTL_CONSTEXPR_FUNC signed char epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC signed char round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC signed char infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC signed char quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC signed char signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC signed char denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT - 1;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<unsigned char> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC unsigned char max() { return UCHAR_MAX; };
		static TCSTL_CONSTEXPR_FUNC unsigned char min() { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char lowest() { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned char denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<wchar_t> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC wchar_t max() TCSTL_NOEXCEPT { return WCHAR_MAX; };
		static TCSTL_CONSTEXPR_FUNC wchar_t min() TCSTL_NOEXCEPT { return WCHAR_MIN; };
		static TCSTL_CONSTEXPR_FUNC wchar_t lowest() TCSTL_NOEXCEPT { return is_signed ? WCHAR_MIN : 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC wchar_t denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = (WCHAR_MIN != 0);
		static TCSTL_CONSTEXPR_VAR bool is_modulo = !is_signed;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(wchar_t) - is_signed;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

#ifdef TCSTL11
	template<> class numeric_limits<char16_t> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC char16_t max() { return USHRT_MAX; };
		static TCSTL_CONSTEXPR_FUNC char16_t min() { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t lowest() { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char16_t denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(char16_t);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<char32_t> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC char32_t max() { return ULONG_MAX; };
		static TCSTL_CONSTEXPR_FUNC char32_t min() { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t lowest() { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC char32_t denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(char32_t);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};
#endif

	template<> class numeric_limits<short> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC short max() TCSTL_NOEXCEPT { return SHRT_MAX; };
		static TCSTL_CONSTEXPR_FUNC short min() TCSTL_NOEXCEPT { return SHRT_MIN; };
		static TCSTL_CONSTEXPR_FUNC short lowest() TCSTL_NOEXCEPT { return SHRT_MIN; };
		static TCSTL_CONSTEXPR_FUNC short epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC short round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC short infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC short quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC short signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC short denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(short) - 1;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<unsigned short> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC unsigned short max() TCSTL_NOEXCEPT { return USHRT_MAX; }
		static TCSTL_CONSTEXPR_FUNC unsigned short min() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned short lowest() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned short epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned short round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned short infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned short quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned short signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned short denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(short);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<int> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC int max() TCSTL_NOEXCEPT { return INT_MAX; }
		static TCSTL_CONSTEXPR_FUNC int min() TCSTL_NOEXCEPT { return INT_MIN; }
		static TCSTL_CONSTEXPR_FUNC int lowest() TCSTL_NOEXCEPT { return INT_MIN; }
		static TCSTL_CONSTEXPR_FUNC int epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC int round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC int infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC int quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC int signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC int denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(int) - 1;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<unsigned int> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC unsigned int max() TCSTL_NOEXCEPT { return UINT_MAX; }
		static TCSTL_CONSTEXPR_FUNC unsigned int min() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned int lowest() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned int epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned int round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned int infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned int quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned int signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned int denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(int);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<long> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC long max() TCSTL_NOEXCEPT { return LONG_MAX; }
		static TCSTL_CONSTEXPR_FUNC long min() TCSTL_NOEXCEPT { return LONG_MIN; }
		static TCSTL_CONSTEXPR_FUNC long lowest() TCSTL_NOEXCEPT { return LONG_MIN; }
		static TCSTL_CONSTEXPR_FUNC long epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(long) - 1;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<unsigned long> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC unsigned long max() TCSTL_NOEXCEPT { return ULONG_MAX; }
		static TCSTL_CONSTEXPR_FUNC unsigned long min() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned long lowest() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned long epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(long);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<long long> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC long long max() TCSTL_NOEXCEPT { return LLONG_MAX; }
		static TCSTL_CONSTEXPR_FUNC long long min() TCSTL_NOEXCEPT { return LLONG_MIN; }
		static TCSTL_CONSTEXPR_FUNC long long lowest() TCSTL_NOEXCEPT { return LLONG_MIN; }
		static TCSTL_CONSTEXPR_FUNC long long epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long long round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long long infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long long quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long long signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC long long denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_signed = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(long long) - 1;
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};

	template<> class numeric_limits<unsigned long long> : public limitsHelper::_integer_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC unsigned long long max() TCSTL_NOEXCEPT { return ULLONG_MAX; }
		static TCSTL_CONSTEXPR_FUNC unsigned long long min() TCSTL_NOEXCEPT { return 0; }
		static TCSTL_CONSTEXPR_FUNC unsigned long long lowest() TCSTL_NOEXCEPT { return(min()); }
		static TCSTL_CONSTEXPR_FUNC unsigned long long epsilon() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long long round_error() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long long infinity() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long long quiet_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long long signaling_NaN() TCSTL_NOEXCEPT { return 0; };
		static TCSTL_CONSTEXPR_FUNC unsigned long long denorm_min() TCSTL_NOEXCEPT { return 0; };

		static TCSTL_CONSTEXPR_VAR bool is_modulo = true;
		static TCSTL_CONSTEXPR_VAR int digits = CHAR_BIT * sizeof(long long);
		static TCSTL_CONSTEXPR_VAR int digits10 = (int)(digits * __TC_LIMITS_LOG10_2_VALUE);
	};
	template<> class numeric_limits<float> :
		public limitsHelper::_floatingpoint_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC float min() TCSTL_NOEXCEPT { return FLT_MIN; };
		static TCSTL_CONSTEXPR_FUNC float max() TCSTL_NOEXCEPT { return FLT_MAX; };
		static TCSTL_CONSTEXPR_FUNC float lowest() TCSTL_NOEXCEPT { return -FLT_MAX; };
		static TCSTL_CONSTEXPR_FUNC float epsilon() TCSTL_NOEXCEPT { return FLT_EPSILON; };
		static TCSTL_CONSTEXPR_FUNC float round_error() TCSTL_NOEXCEPT { return 0.5f; };
#ifdef TCSTL11
		static TCSTL_CONSTEXPR_FUNC float infinity() TCSTL_NOEXCEPT { return __builtin_huge_valf(); }
		static TCSTL_CONSTEXPR_FUNC float quiet_NaN() TCSTL_NOEXCEPT { return __builtin_nanf("0"); };
		static TCSTL_CONSTEXPR_FUNC float signaling_NaN() TCSTL_NOEXCEPT { return __builtin_nansf("1"); };
#else
		static TCSTL_CONSTEXPR_FUNC float infinity() TCSTL_NOEXCEPT { return limitsHelper::__infLimitflt.floatval; }
		static TCSTL_CONSTEXPR_FUNC float quiet_NaN() TCSTL_NOEXCEPT { return limitsHelper::__qNanLimitflt.floatval; };
		static TCSTL_CONSTEXPR_FUNC float signaling_NaN() TCSTL_NOEXCEPT { return limitsHelper::__sNanLimitflt.floatval; };
#endif // TCSTL11
		static TCSTL_CONSTEXPR_FUNC float denorm_min() TCSTL_NOEXCEPT { return FLT_TRUE_MIN; };

		static TCSTL_CONSTEXPR_VAR int digits = FLT_MANT_DIG;
		static TCSTL_CONSTEXPR_VAR int digits10 = FLT_DIG;
		static TCSTL_CONSTEXPR_VAR int max_digits10 = FLT_DECIMAL_DIG;
		static TCSTL_CONSTEXPR_VAR int radix = FLT_RADIX;
		static TCSTL_CONSTEXPR_VAR int min_exponent = FLT_MIN_EXP;
		static TCSTL_CONSTEXPR_VAR int min_exponent10 = FLT_MIN_10_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent = FLT_MAX_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent10 = FLT_MAX_10_EXP;
		static TCSTL_CONSTEXPR_VAR bool tinyness_before = true;
	};


	template<> class numeric_limits<double> :
		public limitsHelper::_floatingpoint_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC double min() TCSTL_NOEXCEPT { return DBL_MIN; };
		static TCSTL_CONSTEXPR_FUNC double max() TCSTL_NOEXCEPT { return DBL_MAX; };
		static TCSTL_CONSTEXPR_FUNC double lowest() TCSTL_NOEXCEPT { return -DBL_MAX; };
		static TCSTL_CONSTEXPR_FUNC double epsilon() TCSTL_NOEXCEPT { return DBL_EPSILON; };
		static TCSTL_CONSTEXPR_FUNC double round_error() TCSTL_NOEXCEPT { return 0.5; };
#ifdef TCSTL11
		static TCSTL_CONSTEXPR_FUNC double infinity() TCSTL_NOEXCEPT { return __builtin_huge_val(); };
		static TCSTL_CONSTEXPR_FUNC double quiet_NaN() TCSTL_NOEXCEPT { return __builtin_nan("0"); };
		static TCSTL_CONSTEXPR_FUNC double signaling_NaN() TCSTL_NOEXCEPT { return __builtin_nans("1"); };
#else
		static TCSTL_CONSTEXPR_FUNC double infinity() TCSTL_NOEXCEPT { return limitsHelper::__infLimitdbl.doubleval; };
		static TCSTL_CONSTEXPR_FUNC double quiet_NaN() TCSTL_NOEXCEPT { return limitsHelper::__qNanLimitdbl.doubleval; };
		static TCSTL_CONSTEXPR_FUNC double signaling_NaN() TCSTL_NOEXCEPT { return limitsHelper::__sNanLimitdbl.doubleval; };
#endif // TCSTL11
		static TCSTL_CONSTEXPR_FUNC double denorm_min() TCSTL_NOEXCEPT { return DBL_TRUE_MIN; };

		static TCSTL_CONSTEXPR_VAR int digits = DBL_MANT_DIG;
		static TCSTL_CONSTEXPR_VAR int digits10 = DBL_DIG;
		static TCSTL_CONSTEXPR_VAR int max_digits10 = DBL_DECIMAL_DIG;
		static TCSTL_CONSTEXPR_VAR int radix = FLT_RADIX;
		static TCSTL_CONSTEXPR_VAR int min_exponent = DBL_MIN_EXP;
		static TCSTL_CONSTEXPR_VAR int min_exponent10 = DBL_MIN_10_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent = DBL_MAX_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent10 = DBL_MAX_10_EXP;
		static TCSTL_CONSTEXPR_VAR bool tinyness_before = true;
	};

	template<> class numeric_limits<long double> :
		public limitsHelper::_floatingpoint_numerical_limits
	{
	public:
		static TCSTL_CONSTEXPR_FUNC long double min() TCSTL_NOEXCEPT { return DBL_MIN; };
		static TCSTL_CONSTEXPR_FUNC long double max() TCSTL_NOEXCEPT { return DBL_MAX; };
		static TCSTL_CONSTEXPR_FUNC long double lowest() TCSTL_NOEXCEPT { return -DBL_MAX; };
		static TCSTL_CONSTEXPR_FUNC long double epsilon() TCSTL_NOEXCEPT { return DBL_EPSILON; };
		static TCSTL_CONSTEXPR_FUNC long double round_error() TCSTL_NOEXCEPT { return 0.5L; };
#ifdef TCSTL11
		static TCSTL_CONSTEXPR_FUNC long double infinity() TCSTL_NOEXCEPT { return __builtin_huge_val(); };
		static TCSTL_CONSTEXPR_FUNC long double quiet_NaN() TCSTL_NOEXCEPT { return __builtin_nan("0"); };
		static TCSTL_CONSTEXPR_FUNC long double signaling_NaN() TCSTL_NOEXCEPT { return __builtin_nans("1"); };
#else
		static TCSTL_CONSTEXPR_FUNC long double infinity() TCSTL_NOEXCEPT { return limitsHelper::__infLimitdbl.ldoubleval;};
		static TCSTL_CONSTEXPR_FUNC long double quiet_NaN() TCSTL_NOEXCEPT { return limitsHelper::__qNanLimitdbl.ldoubleval;};
		static TCSTL_CONSTEXPR_FUNC long double signaling_NaN() TCSTL_NOEXCEPT { return limitsHelper::__sNanLimitdbl.ldoubleval; };
#endif // TCSTL11
		static TCSTL_CONSTEXPR_FUNC long double denorm_min() TCSTL_NOEXCEPT { return DBL_TRUE_MIN; };

		static TCSTL_CONSTEXPR_VAR int digits = DBL_MANT_DIG;
		static TCSTL_CONSTEXPR_VAR int digits10 = DBL_DIG;
		static TCSTL_CONSTEXPR_VAR int max_digits10 = DBL_DECIMAL_DIG;
		static TCSTL_CONSTEXPR_VAR int radix = FLT_RADIX;
		static TCSTL_CONSTEXPR_VAR int min_exponent = DBL_MIN_EXP;
		static TCSTL_CONSTEXPR_VAR int min_exponent10 = DBL_MIN_10_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent = DBL_MAX_EXP;
		static TCSTL_CONSTEXPR_VAR int max_exponent10 = DBL_MAX_10_EXP;
		static TCSTL_CONSTEXPR_VAR bool tinyness_before = true;
	};
}

// DISABLE_TWINCAT_STL
#endif
// include guard
#endif
