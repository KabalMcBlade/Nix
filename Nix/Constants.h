#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"


NIX_NAMESPACE_BEGIN

#ifdef max
#undef max
#endif //

#ifdef min
#undef min
#endif //


#define NIX_VALUE_DEGTORAD  0.017453292519943295769236907684886f    // Degrees to Radians (PI/180)
#define NIX_VALUE_RADTODEG  57.295779513082320876798154814105f      // Radians to Degrees (180/PI)
#define NIX_DEG_TO_RAD(x)   (x * NIX_VALUE_DEGTORAD)
#define NIX_RAD_TO_DEG(x)   (x * NIX_VALUE_RADTODEG)

static constexpr uint32 kuOne = 0x00000001;
static constexpr uint32 kuTwo = 0x00000002;
static constexpr uint32 kuFour = 0x00000004;
static constexpr uint32 ku127 = 0x0000007f;
static constexpr uint32 kuOneNeg = ~kuOne;
static constexpr uint32 kuSignBit = 0x80000000;
static constexpr uint32 kuSignBitNeg = ~kuSignBit;
static constexpr uint32 kuZero = 0x00000000;
static constexpr uint32 kuZeroNeg = ~kuZero;

static constexpr float kfZero = 0.0f;
static constexpr float kfOne = 1.0f;
static constexpr float kfMinusOne = -1.0f;
static constexpr float kfHalf = 0.5f;
static constexpr float kf255 = 255.0f;
static constexpr float kfMinChar = -128.0f;
static constexpr float kfMaxChar = 127.0f;
static constexpr float kfMinShort = -32768.0f;
static constexpr float kfMaxShort = 32767.0f;
static constexpr float kf255Over2 = 127.5f;

static constexpr float kfSmallNumber = 1.e-8f;
static constexpr float kfBigNumber = 1.e+8f;

constexpr static const float kfPI = 3.141592653589793238f;
constexpr static const float kfInv2PI = 0.1591549f;
constexpr static const float kf2PI = 6.283185f;
constexpr static const float kfHalfPI = 1.5707963267948966192f;
constexpr static const float kf3halfPI = 4.7123889f;
constexpr static const float kfQuarterPI = 0.7853981633974483096f;   // pi/4
constexpr static const float kfOrbitalPI = 1.27323954473516f;        // 4/Pi

constexpr static const float kfEpsilon = std::numeric_limits<float>::epsilon();
constexpr static const float kfMin = std::numeric_limits<float>::min();
constexpr static const float kfMax = std::numeric_limits<float>::max();
constexpr static const float kfMinusInf = -std::numeric_limits<float>::infinity();
constexpr static const float kfPlusInf = std::numeric_limits<float>::infinity();

// minus cephes
constexpr static const float kfNegDP1 = 0.78515625f; 
constexpr static const float kfNegDP2 = 2.4187564849853515625e-4f;
constexpr static const float kfNegDP3 = 3.77489497744594108e-8f;

// tan chephes
constexpr static const float kfTanCP0 = 9.38540185543E-3f;
constexpr static const float kfTanCP1 = 3.11992232697E-3f;
constexpr static const float kfTanCP2 = 2.44301354525E-2f;
constexpr static const float kfTanCP3 = 5.34112807005E-2f;
constexpr static const float kfTanCP4 = 1.33387994085E-1f;
constexpr static const float kfTanCP5 = 3.33331568548E-1f;
constexpr static const float kfTanHI = 2.414213562373095f;
constexpr static const float kfTanLO = 0.4142135623730950f;
constexpr static const float kfTanP0 = 8.05374449538e-2f;
constexpr static const float kfTanP1 = 1.38776856032E-1f;
constexpr static const float kfTanP2 = 1.99777106478E-1f;
constexpr static const float kfTanP3 = 3.33329491539E-1f;


NIX_ALIGN_16 struct Constants
{
    NIX_INLINE Constants(uint32 _0, uint32 _1, uint32 _2, uint32 _3)
    {
        m_ui[0] = _0;
        m_ui[1] = _1;
        m_ui[2] = _2;
        m_ui[3] = _3;
    }
    NIX_INLINE Constants(int32 _0, int32 _1, int32 _2, int32 _3)
    {
        m_si[0] = _0;
        m_si[1] = _1;
        m_si[2] = _2;
        m_si[3] = _3;
    }
    NIX_INLINE Constants(float _0, float _1, float _2, float _3)
    {
        m_f[0] = _0;
        m_f[1] = _1;
        m_f[2] = _2;
        m_f[3] = _3;
    }

    union
    {
        uint32      m_ui[4];
        int32      m_si[4];
        float    m_f[4];
        float128   m_simdf;
        int128     m_simfi;
    };

    NIX_INLINE operator float128() const { return m_simdf; }
    NIX_INLINE operator int128() const { return m_simfi; }
};

NIX_MATH_CONST Constants kOneNeg = { kuOneNeg, kuOneNeg, kuOneNeg, kuOneNeg };
NIX_MATH_CONST Constants kSignBit = { kuSignBit, kuSignBit, kuSignBit, kuSignBit };
NIX_MATH_CONST Constants kNotAll = { kuSignBitNeg, kuSignBitNeg, kuSignBitNeg, kuSignBitNeg };
NIX_MATH_CONST Constants kNegSignBit = { kuZeroNeg, kuZeroNeg, kuZeroNeg, kuZeroNeg };
NIX_MATH_CONST Constants kMaskZeroSignSignZero = { kuZero, kuSignBit, kuSignBit, kuZero };
NIX_MATH_CONST Constants kMaskSignZeroSignZero = { kuSignBit, kuZero, kuSignBit, kuZero };
NIX_MATH_CONST Constants kMaskZeroSignZeroSign = { kuZero, kuSignBit, kuZero, kuSignBit };
NIX_MATH_CONST Constants kMaskSignSignZeroZero = { kuSignBit, kuSignBit, kuZero, kuZero };
NIX_MATH_CONST Constants kTwo = { kuTwo, kuTwo, kuTwo, kuTwo };
NIX_MATH_CONST Constants kFour = { kuFour, kuFour, kuFour, kuFour };
NIX_MATH_CONST Constants k127 = { ku127, ku127, ku127, ku127 };

NIX_MATH_CONST Constants kZero = { kfZero, kfZero, kfZero, kfZero };
NIX_MATH_CONST Constants kOne = { kfOne, kfOne, kfOne, kfOne };
NIX_MATH_CONST Constants kMinusOne = { kfMinusOne, kfMinusOne, kfMinusOne, kfMinusOne };
NIX_MATH_CONST Constants kHalf = { kfHalf, kfHalf, kfHalf, kfHalf };
NIX_MATH_CONST Constants k255 = { kf255, kf255, kf255, kf255 };
NIX_MATH_CONST Constants k255Over2 = { kf255Over2, kf255Over2, kf255Over2, kf255Over2 };

NIX_MATH_CONST Constants k0001 = { kfZero, kfZero, kfZero, kfOne };
NIX_MATH_CONST Constants k1110 = { kfOne, kfOne, kfOne, kfZero };

NIX_MATH_CONST Constants kMin = { kfMin, kfMin, kfMin, kfMin };
NIX_MATH_CONST Constants kMax = { kfMax, kfMax, kfMax, kfMax };
NIX_MATH_CONST Constants kMinusInf = { kfMinusInf, kfMinusInf, kfMinusInf, kfMinusInf };
NIX_MATH_CONST Constants kPlusInf = { kfPlusInf, kfPlusInf, kfPlusInf, kfPlusInf };

NIX_MATH_CONST Constants kSmallNumber = { kfSmallNumber, kfSmallNumber, kfSmallNumber, kfSmallNumber };
NIX_MATH_CONST Constants kBigNumber = { kfBigNumber, kfBigNumber, kfBigNumber, kfBigNumber };

NIX_MATH_CONST Constants kPI = { kfPI, kfPI, kfPI, kfPI };
NIX_MATH_CONST Constants kHalfPI = { kfHalfPI, kfHalfPI, kfHalfPI, kfHalfPI };
NIX_MATH_CONST Constants kQuartPI = { kfQuarterPI, kfQuarterPI, kfQuarterPI, kfQuarterPI };
NIX_MATH_CONST Constants kOrbitalPI = { kfOrbitalPI, kfOrbitalPI, kfOrbitalPI, kfOrbitalPI };

NIX_MATH_CONST Constants kNegDP1 = { kfNegDP1, kfNegDP1, kfNegDP1, kfNegDP1 };
NIX_MATH_CONST Constants kNegDP2 = { kfNegDP2, kfNegDP2, kfNegDP2, kfNegDP2 };
NIX_MATH_CONST Constants kNegDP3 = { kfNegDP3, kfNegDP3, kfNegDP3, kfNegDP3 };

NIX_MATH_CONST Constants kTanCP0 = { kfTanCP0, kfTanCP0, kfTanCP0, kfTanCP0 };
NIX_MATH_CONST Constants kTanCP1 = { kfTanCP1, kfTanCP1, kfTanCP1, kfTanCP1 };
NIX_MATH_CONST Constants kTanCP2 = { kfTanCP2, kfTanCP2, kfTanCP2, kfTanCP2 };
NIX_MATH_CONST Constants kTanCP3 = { kfTanCP3, kfTanCP3, kfTanCP3, kfTanCP3 };
NIX_MATH_CONST Constants kTanCP4 = { kfTanCP4, kfTanCP4, kfTanCP4, kfTanCP4 };
NIX_MATH_CONST Constants kTanCP5 = { kfTanCP5, kfTanCP5, kfTanCP5, kfTanCP5 };
NIX_MATH_CONST Constants kTanHI = { kfTanHI, kfTanHI, kfTanHI, kfTanHI };
NIX_MATH_CONST Constants kTanLO = { kfTanLO, kfTanLO, kfTanLO, kfTanLO };
NIX_MATH_CONST Constants kTanP0 = { kfTanP0, kfTanP0, kfTanP0, kfTanP0 };
NIX_MATH_CONST Constants kTanP1 = { kfTanP1, kfTanP1, kfTanP1, kfTanP1 };
NIX_MATH_CONST Constants kTanP2 = { kfTanP2, kfTanP2, kfTanP2, kfTanP2 };
NIX_MATH_CONST Constants kTanP3 = { kfTanP3, kfTanP3, kfTanP3, kfTanP3 };


NIX_NAMESPACE_END
