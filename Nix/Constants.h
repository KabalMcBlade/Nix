#pragma once

#include "Architecture.h"
#include "CoreDefs.h"

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

static constexpr nixU32 kuOne = 0x00000001;
static constexpr nixU32 kuTwo = 0x00000002;
static constexpr nixU32 kuFour = 0x00000004;
static constexpr nixU32 ku127 = 0x0000007f;
static constexpr nixU32 kuOneNeg = ~kuOne;
static constexpr nixU32 kuSignBit = 0x80000000;
static constexpr nixU32 kuSignBitNeg = ~kuSignBit;
static constexpr nixU32 kuZero = 0x00000000;
static constexpr nixU32 kuZeroNeg = ~kuZero;

static constexpr nixFloat kfZero = 0.0f;
static constexpr nixFloat kfOne = 1.0f;
static constexpr nixFloat kfMinusOne = -1.0f;
static constexpr nixFloat kfHalf = 0.5f;
static constexpr nixFloat kf255 = 255.0f;
static constexpr nixFloat kfMinChar = -128.0f;
static constexpr nixFloat kfMaxChar = 127.0f;
static constexpr nixFloat kfMinShort = -32768.0f;
static constexpr nixFloat kfMaxShort = 32767.0f;
static constexpr nixFloat kf255Over2 = 127.5f;

static constexpr nixFloat kfSmallNumber = 1.e-8f;
static constexpr nixFloat kfBigNumber = 1.e+8f;

constexpr static const nixFloat kfPI = 3.141592653589793238f;
constexpr static const nixFloat kfInv2PI = 0.1591549f;
constexpr static const nixFloat kf2PI = 6.283185f;
constexpr static const nixFloat kfHalfPI = 1.5707963267948966192f;
constexpr static const nixFloat kf3halfPI = 4.7123889f;
constexpr static const nixFloat kfQuarterPI = 0.7853981633974483096f;   // pi/4
constexpr static const nixFloat kfOrbitalPI = 1.27323954473516f;        // 4/Pi

constexpr static const nixFloat kfEpsilon = std::numeric_limits<nixFloat>::epsilon();
constexpr static const nixFloat kfMin = std::numeric_limits<nixFloat>::min();
constexpr static const nixFloat kfMax = std::numeric_limits<nixFloat>::max();
constexpr static const nixFloat kfMinusInf = -std::numeric_limits<nixFloat>::infinity();
constexpr static const nixFloat kfPlusInf = std::numeric_limits<nixFloat>::infinity();

// minus cephes
constexpr static const nixFloat kfNegDP1 = 0.78515625f; 
constexpr static const nixFloat kfNegDP2 = 2.4187564849853515625e-4f;
constexpr static const nixFloat kfNegDP3 = 3.77489497744594108e-8f;

// tan chephes
constexpr static const nixFloat kfTanCP0 = 9.38540185543E-3f;
constexpr static const nixFloat kfTanCP1 = 3.11992232697E-3f;
constexpr static const nixFloat kfTanCP2 = 2.44301354525E-2f;
constexpr static const nixFloat kfTanCP3 = 5.34112807005E-2f;
constexpr static const nixFloat kfTanCP4 = 1.33387994085E-1f;
constexpr static const nixFloat kfTanCP5 = 3.33331568548E-1f;
constexpr static const nixFloat kfTanHI = 2.414213562373095f;
constexpr static const nixFloat kfTanLO = 0.4142135623730950f;
constexpr static const nixFloat kfTanP0 = 8.05374449538e-2f;
constexpr static const nixFloat kfTanP1 = 1.38776856032E-1f;
constexpr static const nixFloat kfTanP2 = 1.99777106478E-1f;
constexpr static const nixFloat kfTanP3 = 3.33329491539E-1f;


NIX_SIMD_ALIGN_16 struct Constants
{
    NIX_INLINE Constants(nixU32 _0, nixU32 _1, nixU32 _2, nixU32 _3)
    {
        m_ui[0] = _0;
        m_ui[1] = _1;
        m_ui[2] = _2;
        m_ui[3] = _3;
    }
    NIX_INLINE Constants(nixS32 _0, nixS32 _1, nixS32 _2, nixS32 _3)
    {
        m_si[0] = _0;
        m_si[1] = _1;
        m_si[2] = _2;
        m_si[3] = _3;
    }
    NIX_INLINE Constants(nixFloat _0, nixFloat _1, nixFloat _2, nixFloat _3)
    {
        m_f[0] = _0;
        m_f[1] = _1;
        m_f[2] = _2;
        m_f[3] = _3;
    }

    union
    {
        nixU32      m_ui[4];
        nixS32      m_si[4];
        nixFloat    m_f[4];
        nixFloat4   m_simdf;
        nixInt4     m_simfi;
    };

    NIX_INLINE operator nixFloat4() const { return m_simdf; }
    NIX_INLINE operator nixInt4() const { return m_simfi; }
};

NIX_CONST Constants kOneNeg = { kuOneNeg, kuOneNeg, kuOneNeg, kuOneNeg };
NIX_CONST Constants kSignBit = { kuSignBit, kuSignBit, kuSignBit, kuSignBit };
NIX_CONST Constants kNotAll = { kuSignBitNeg, kuSignBitNeg, kuSignBitNeg, kuSignBitNeg };
NIX_CONST Constants kNegSignBit = { kuZeroNeg, kuZeroNeg, kuZeroNeg, kuZeroNeg };
NIX_CONST Constants kMaskZeroSignSignZero = { kuZero, kuSignBit, kuSignBit, kuZero };
NIX_CONST Constants kMaskSignZeroSignZero = { kuSignBit, kuZero, kuSignBit, kuZero };
NIX_CONST Constants kMaskZeroSignZeroSign = { kuZero, kuSignBit, kuZero, kuSignBit };
NIX_CONST Constants kMaskSignSignZeroZero = { kuSignBit, kuSignBit, kuZero, kuZero };
NIX_CONST Constants kTwo = { kuTwo, kuTwo, kuTwo, kuTwo };
NIX_CONST Constants kFour = { kuFour, kuFour, kuFour, kuFour };
NIX_CONST Constants k127 = { ku127, ku127, ku127, ku127 };

NIX_CONST Constants kZero = { kfZero, kfZero, kfZero, kfZero };
NIX_CONST Constants kOne = { kfOne, kfOne, kfOne, kfOne };
NIX_CONST Constants kMinusOne = { kfMinusOne, kfMinusOne, kfMinusOne, kfMinusOne };
NIX_CONST Constants kHalf = { kfHalf, kfHalf, kfHalf, kfHalf };
NIX_CONST Constants k255 = { kf255, kf255, kf255, kf255 };
NIX_CONST Constants k255Over2 = { kf255Over2, kf255Over2, kf255Over2, kf255Over2 };

NIX_CONST Constants k0001 = { kfZero, kfZero, kfZero, kfOne };
NIX_CONST Constants k1110 = { kfOne, kfOne, kfOne, kfZero };

NIX_CONST Constants kMin = { kfMin, kfMin, kfMin, kfMin };
NIX_CONST Constants kMax = { kfMax, kfMax, kfMax, kfMax };
NIX_CONST Constants kMinusInf = { kfMinusInf, kfMinusInf, kfMinusInf, kfMinusInf };
NIX_CONST Constants kPlusInf = { kfPlusInf, kfPlusInf, kfPlusInf, kfPlusInf };

NIX_CONST Constants kSmallNumber = { kfSmallNumber, kfSmallNumber, kfSmallNumber, kfSmallNumber };
NIX_CONST Constants kBigNumber = { kfBigNumber, kfBigNumber, kfBigNumber, kfBigNumber };

NIX_CONST Constants kPI = { kfPI, kfPI, kfPI, kfPI };
NIX_CONST Constants kHalfPI = { kfHalfPI, kfHalfPI, kfHalfPI, kfHalfPI };
NIX_CONST Constants kQuartPI = { kfQuarterPI, kfQuarterPI, kfQuarterPI, kfQuarterPI };
NIX_CONST Constants kOrbitalPI = { kfOrbitalPI, kfOrbitalPI, kfOrbitalPI, kfOrbitalPI };

NIX_CONST Constants kNegDP1 = { kfNegDP1, kfNegDP1, kfNegDP1, kfNegDP1 };
NIX_CONST Constants kNegDP2 = { kfNegDP2, kfNegDP2, kfNegDP2, kfNegDP2 };
NIX_CONST Constants kNegDP3 = { kfNegDP3, kfNegDP3, kfNegDP3, kfNegDP3 };

NIX_CONST Constants kTanCP0 = { kfTanCP0, kfTanCP0, kfTanCP0, kfTanCP0 };
NIX_CONST Constants kTanCP1 = { kfTanCP1, kfTanCP1, kfTanCP1, kfTanCP1 };
NIX_CONST Constants kTanCP2 = { kfTanCP2, kfTanCP2, kfTanCP2, kfTanCP2 };
NIX_CONST Constants kTanCP3 = { kfTanCP3, kfTanCP3, kfTanCP3, kfTanCP3 };
NIX_CONST Constants kTanCP4 = { kfTanCP4, kfTanCP4, kfTanCP4, kfTanCP4 };
NIX_CONST Constants kTanCP5 = { kfTanCP5, kfTanCP5, kfTanCP5, kfTanCP5 };
NIX_CONST Constants kTanHI = { kfTanHI, kfTanHI, kfTanHI, kfTanHI };
NIX_CONST Constants kTanLO = { kfTanLO, kfTanLO, kfTanLO, kfTanLO };
NIX_CONST Constants kTanP0 = { kfTanP0, kfTanP0, kfTanP0, kfTanP0 };
NIX_CONST Constants kTanP1 = { kfTanP1, kfTanP1, kfTanP1, kfTanP1 };
NIX_CONST Constants kTanP2 = { kfTanP2, kfTanP2, kfTanP2, kfTanP2 };
NIX_CONST Constants kTanP3 = { kfTanP3, kfTanP3, kfTanP3, kfTanP3 };


NIX_NAMESPACE_END
