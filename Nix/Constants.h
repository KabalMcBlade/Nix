#pragma once


#include "Conversion.h"


#pragma warning(push)
#pragma warning(disable: 4838 4305)

NIX_NAMESPACE_BEGIN

#define NIX_PI 3.141592653589793238f
#define NIX_HALF_PI 1.5707963267948966192f

#define NIX_VALUE_DEGTORAD  0.017453292519943295769236907684886f    // Degrees to Radians (PI/180)
#define NIX_VALUE_RADTODEG  57.295779513082320876798154814105f      // Radians to Degrees (180/PI)
#define NIX_DEG_TO_RAD(x)   (x * NIX_VALUE_DEGTORAD)
#define NIX_RAD_TO_DEG(x)   (x * NIX_VALUE_RADTODEG)

#define NIX_SMALL_NUMBER	(1.e-8f)
#define NIX_BIG_NUMBER	(1.e+8f)


#define NIX_MINUS_INFINITE	(-std::numeric_limits<float>::infinity())
#define NIX_PLUS_INFINITE	(std::numeric_limits<float>::infinity())
#define NIX_EPSILON			(std::numeric_limits<float>::epsilon())


#define NIX_ZERO 0x00000000
#define NIX_SIGN_BIT 0x80000000
#define NIX_SIGN_BIT_NEG 0x7FFFFFF




// numerical
NIX_MATH_CONST Float128 kZero = { { { 0.0f, 0.0f, 0.0f, 0.0f } } };
NIX_MATH_CONST Float128 kOneVec4 = { { { 1.0f, 1.0f, 1.0f, 1.0f } } };
NIX_MATH_CONST Float128 kOneVec3 = { { { 1.0f, 1.0f, 1.0f, 0.0f } } };
NIX_MATH_CONST Float128 kMinusOneVec4 = { { { -1.0f, -1.0f, -1.0f, -1.0f } } };
NIX_MATH_CONST Float128 kMinusOneVec3 = { { { -1.0f, -1.0f, -1.0f, 0.0f } } };
NIX_MATH_CONST Float128 kOneHalfVec4 = { { { 0.5f, 0.5f, 0.5f, 0.5f } } };
NIX_MATH_CONST Float128 kOneHalfVec3 = { { { 0.5f, 0.5f, 0.5f, 0.0f } } };
NIX_MATH_CONST Float128 kIdentity0 = { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
NIX_MATH_CONST Float128 kIdentity1 = { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
NIX_MATH_CONST Float128 kIdentity2 = { { { 0.0f, 0.0f, 1.0f, 0.0f } } };
NIX_MATH_CONST Float128 kIdentity3 = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
NIX_MATH_CONST Float128 k255Vec4 = { { { 255.0f, 255.0f, 255.0f, 255.0f } } };
NIX_MATH_CONST Float128 k255Vec3 = { { { 255.0f, 255.0f, 255.0f, 0.0f } } };
NIX_MATH_CONST Float128 k255Over2Vec4 = { { { 127.5f, 127.5f, 127.5f, 127.5f } } };
NIX_MATH_CONST Float128 k255Over2Vec3 = { { { 127.5f, 127.5f, 127.5f, 0.0f } } };


NIX_MATH_CONST Float128 kMinusInf = { NIX_MINUS_INFINITE, NIX_MINUS_INFINITE, NIX_MINUS_INFINITE, NIX_MINUS_INFINITE };
NIX_MATH_CONST Float128 kPlusInf = { NIX_PLUS_INFINITE, NIX_PLUS_INFINITE, NIX_PLUS_INFINITE, NIX_PLUS_INFINITE };
NIX_MATH_CONST Float128 kSignBit = { NIX_SIGN_BIT, NIX_SIGN_BIT, NIX_SIGN_BIT, NIX_SIGN_BIT };
NIX_MATH_CONST Float128 kNotAll = { NIX_SIGN_BIT_NEG, NIX_SIGN_BIT_NEG, NIX_SIGN_BIT_NEG, NIX_SIGN_BIT_NEG };
NIX_MATH_CONST Float128 kSmallNumber = { NIX_SMALL_NUMBER, NIX_SMALL_NUMBER, NIX_SMALL_NUMBER, NIX_SMALL_NUMBER };
NIX_MATH_CONST Float128 kBigNumber = { NIX_BIG_NUMBER, NIX_BIG_NUMBER, NIX_BIG_NUMBER, NIX_BIG_NUMBER };
NIX_MATH_CONST Float128 kMaskSignZeroSignZero = { NIX_SIGN_BIT, NIX_ZERO, NIX_SIGN_BIT, NIX_ZERO };


// selection
NIX_MATH_CONST UInt128 kSelectX = { { { 0xFFFFFFFF, 0, 0, 0 } } };
NIX_MATH_CONST UInt128 kSelectY = { { { 0, 0xFFFFFFFF, 0, 0 } } };
NIX_MATH_CONST UInt128 kSelectZ = { { { 0, 0, 0xFFFFFFFF, 0 } } };
NIX_MATH_CONST UInt128 kSelectW = { { { 0, 0, 0, 0xFFFFFFFF } } };


NIX_NAMESPACE_END

#pragma warning(pop)