#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Constants.h"

NIX_NAMESPACE_BEGIN

#define SWIZZLE(V, X, Y, Z, W) nixFloat4(_mm_shuffle_ps(V, V, _MM_SHUFFLE(W, Z, Y, X)))

NIX_SIMD_ALIGN_16 struct Swizzle
{
    static NIX_INLINE nixFloat4 XXXX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 0); }
    static NIX_INLINE nixFloat4 XXXY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 1); }
    static NIX_INLINE nixFloat4 XXXZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 2); }
    static NIX_INLINE nixFloat4 XXXW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 3); }
    static NIX_INLINE nixFloat4 XXYX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 0); }
    static NIX_INLINE nixFloat4 XXYY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 1); }
    static NIX_INLINE nixFloat4 XXYZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 2); }
    static NIX_INLINE nixFloat4 XXYW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 3); }
    static NIX_INLINE nixFloat4 XXZX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 0); }
    static NIX_INLINE nixFloat4 XXZY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 1); }
    static NIX_INLINE nixFloat4 XXZZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 2); }
    static NIX_INLINE nixFloat4 XXZW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 3); }
    static NIX_INLINE nixFloat4 XXWX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 0); }
    static NIX_INLINE nixFloat4 XXWY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 1); }
    static NIX_INLINE nixFloat4 XXWZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 2); }
    static NIX_INLINE nixFloat4 XXWW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 3); }
    static NIX_INLINE nixFloat4 XYXX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 0); }
    static NIX_INLINE nixFloat4 XYXY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 1); }
    static NIX_INLINE nixFloat4 XYXZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 2); }
    static NIX_INLINE nixFloat4 XYXW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 3); }
    static NIX_INLINE nixFloat4 XYYX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 0); }
    static NIX_INLINE nixFloat4 XYYY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 1); }
    static NIX_INLINE nixFloat4 XYYZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 2); }
    static NIX_INLINE nixFloat4 XYYW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 3); }
    static NIX_INLINE nixFloat4 XYZX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 0); }
    static NIX_INLINE nixFloat4 XYZY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 1); }
    static NIX_INLINE nixFloat4 XYZZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 2); }
    static NIX_INLINE nixFloat4 XYZW(const nixFloat4& _v) { return _v; }
    static NIX_INLINE nixFloat4 XYWX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 0); }
    static NIX_INLINE nixFloat4 XYWY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 1); }
    static NIX_INLINE nixFloat4 XYWZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 2); }
    static NIX_INLINE nixFloat4 XYWW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 3); }
    static NIX_INLINE nixFloat4 XZXX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 0); }
    static NIX_INLINE nixFloat4 XZXY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 1); }
    static NIX_INLINE nixFloat4 XZXZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 2); }
    static NIX_INLINE nixFloat4 XZXW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 3); }
    static NIX_INLINE nixFloat4 XZYX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 0); }
    static NIX_INLINE nixFloat4 XZYY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 1); }
    static NIX_INLINE nixFloat4 XZYZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 2); }
    static NIX_INLINE nixFloat4 XZYW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 3); }
    static NIX_INLINE nixFloat4 XZZX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 0); }
    static NIX_INLINE nixFloat4 XZZY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 1); }
    static NIX_INLINE nixFloat4 XZZZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 2); }
    static NIX_INLINE nixFloat4 XZZW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 3); }
    static NIX_INLINE nixFloat4 XZWX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 0); }
    static NIX_INLINE nixFloat4 XZWY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 1); }
    static NIX_INLINE nixFloat4 XZWZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 2); }
    static NIX_INLINE nixFloat4 XZWW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 3); }
    static NIX_INLINE nixFloat4 XWXX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 0); }
    static NIX_INLINE nixFloat4 XWXY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 1); }
    static NIX_INLINE nixFloat4 XWXZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 2); }
    static NIX_INLINE nixFloat4 XWXW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 3); }
    static NIX_INLINE nixFloat4 XWYX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 0); }
    static NIX_INLINE nixFloat4 XWYY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 1); }
    static NIX_INLINE nixFloat4 XWYZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 2); }
    static NIX_INLINE nixFloat4 XWYW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 3); }
    static NIX_INLINE nixFloat4 XWZX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 0); }
    static NIX_INLINE nixFloat4 XWZY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 1); }
    static NIX_INLINE nixFloat4 XWZZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 2); }
    static NIX_INLINE nixFloat4 XWZW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 3); }
    static NIX_INLINE nixFloat4 XWWX(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 0); }
    static NIX_INLINE nixFloat4 XWWY(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 1); }
    static NIX_INLINE nixFloat4 XWWZ(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 2); }
    static NIX_INLINE nixFloat4 XWWW(const nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 3); }

    static NIX_INLINE nixFloat4 YXXX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 0); }
    static NIX_INLINE nixFloat4 YXXY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 1); }
    static NIX_INLINE nixFloat4 YXXZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 2); }
    static NIX_INLINE nixFloat4 YXXW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 3); }
    static NIX_INLINE nixFloat4 YXYX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 0); }
    static NIX_INLINE nixFloat4 YXYY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 1); }
    static NIX_INLINE nixFloat4 YXYZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 2); }
    static NIX_INLINE nixFloat4 YXYW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 3); }
    static NIX_INLINE nixFloat4 YXZX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 0); }
    static NIX_INLINE nixFloat4 YXZY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 1); }
    static NIX_INLINE nixFloat4 YXZZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 2); }
    static NIX_INLINE nixFloat4 YXZW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 3); }
    static NIX_INLINE nixFloat4 YXWX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 0); }
    static NIX_INLINE nixFloat4 YXWY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 1); }
    static NIX_INLINE nixFloat4 YXWZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 2); }
    static NIX_INLINE nixFloat4 YXWW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 3); }
    static NIX_INLINE nixFloat4 YYXX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 0); }
    static NIX_INLINE nixFloat4 YYXY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 1); }
    static NIX_INLINE nixFloat4 YYXZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 2); }
    static NIX_INLINE nixFloat4 YYXW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 3); }
    static NIX_INLINE nixFloat4 YYYX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 0); }
    static NIX_INLINE nixFloat4 YYYY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 1); }
    static NIX_INLINE nixFloat4 YYYZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 2); }
    static NIX_INLINE nixFloat4 YYYW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 3); }
    static NIX_INLINE nixFloat4 YYZX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 0); }
    static NIX_INLINE nixFloat4 YYZY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 1); }
    static NIX_INLINE nixFloat4 YYZZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 2); }
    static NIX_INLINE nixFloat4 YYZW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 3); }
    static NIX_INLINE nixFloat4 YYWX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 0); }
    static NIX_INLINE nixFloat4 YYWY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 1); }
    static NIX_INLINE nixFloat4 YYWZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 2); }
    static NIX_INLINE nixFloat4 YYWW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 3); }
    static NIX_INLINE nixFloat4 YZXX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 0); }
    static NIX_INLINE nixFloat4 YZXY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 1); }
    static NIX_INLINE nixFloat4 YZXZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 2); }
    static NIX_INLINE nixFloat4 YZXW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 3); }
    static NIX_INLINE nixFloat4 YZYX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 0); }
    static NIX_INLINE nixFloat4 YZYY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 1); }
    static NIX_INLINE nixFloat4 YZYZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 2); }
    static NIX_INLINE nixFloat4 YZYW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 3); }
    static NIX_INLINE nixFloat4 YZZX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 0); }
    static NIX_INLINE nixFloat4 YZZY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 1); }
    static NIX_INLINE nixFloat4 YZZZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 2); }
    static NIX_INLINE nixFloat4 YZZW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 3); }
    static NIX_INLINE nixFloat4 YZWX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 0); }
    static NIX_INLINE nixFloat4 YZWY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 1); }
    static NIX_INLINE nixFloat4 YZWZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 2); }
    static NIX_INLINE nixFloat4 YZWW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 3); }
    static NIX_INLINE nixFloat4 YWXX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 0); }
    static NIX_INLINE nixFloat4 YWXY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 1); }
    static NIX_INLINE nixFloat4 YWXZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 2); }
    static NIX_INLINE nixFloat4 YWXW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 3); }
    static NIX_INLINE nixFloat4 YWYX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 0); }
    static NIX_INLINE nixFloat4 YWYY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 1); }
    static NIX_INLINE nixFloat4 YWYZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 2); }
    static NIX_INLINE nixFloat4 YWYW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 3); }
    static NIX_INLINE nixFloat4 YWZX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 0); }
    static NIX_INLINE nixFloat4 YWZY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 1); }
    static NIX_INLINE nixFloat4 YWZZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 2); }
    static NIX_INLINE nixFloat4 YWZW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 3); }
    static NIX_INLINE nixFloat4 YWWX(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 0); }
    static NIX_INLINE nixFloat4 YWWY(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 1); }
    static NIX_INLINE nixFloat4 YWWZ(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 2); }
    static NIX_INLINE nixFloat4 YWWW(const nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 3); }

    static NIX_INLINE nixFloat4 ZXXX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 0); }
    static NIX_INLINE nixFloat4 ZXXY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 1); }
    static NIX_INLINE nixFloat4 ZXXZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 2); }
    static NIX_INLINE nixFloat4 ZXXW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 3); }
    static NIX_INLINE nixFloat4 ZXYX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 0); }
    static NIX_INLINE nixFloat4 ZXYY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 1); }
    static NIX_INLINE nixFloat4 ZXYZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 2); }
    static NIX_INLINE nixFloat4 ZXYW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 3); }
    static NIX_INLINE nixFloat4 ZXZX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 0); }
    static NIX_INLINE nixFloat4 ZXZY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 1); }
    static NIX_INLINE nixFloat4 ZXZZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 2); }
    static NIX_INLINE nixFloat4 ZXZW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 3); }
    static NIX_INLINE nixFloat4 ZXWX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 0); }
    static NIX_INLINE nixFloat4 ZXWY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 1); }
    static NIX_INLINE nixFloat4 ZXWZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 2); }
    static NIX_INLINE nixFloat4 ZXWW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 3); }
    static NIX_INLINE nixFloat4 ZYXX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 0); }
    static NIX_INLINE nixFloat4 ZYXY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 1); }
    static NIX_INLINE nixFloat4 ZYXZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 2); }
    static NIX_INLINE nixFloat4 ZYXW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 3); }
    static NIX_INLINE nixFloat4 ZYYX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 0); }
    static NIX_INLINE nixFloat4 ZYYY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 1); }
    static NIX_INLINE nixFloat4 ZYYZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 2); }
    static NIX_INLINE nixFloat4 ZYYW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 3); }
    static NIX_INLINE nixFloat4 ZYZX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 0); }
    static NIX_INLINE nixFloat4 ZYZY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 1); }
    static NIX_INLINE nixFloat4 ZYZZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 2); }
    static NIX_INLINE nixFloat4 ZYZW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 3); }
    static NIX_INLINE nixFloat4 ZYWX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 0); }
    static NIX_INLINE nixFloat4 ZYWY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 1); }
    static NIX_INLINE nixFloat4 ZYWZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 2); }
    static NIX_INLINE nixFloat4 ZYWW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 3); }
    static NIX_INLINE nixFloat4 ZZXX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 0); }
    static NIX_INLINE nixFloat4 ZZXY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 1); }
    static NIX_INLINE nixFloat4 ZZXZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 2); }
    static NIX_INLINE nixFloat4 ZZXW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 3); }
    static NIX_INLINE nixFloat4 ZZYX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 0); }
    static NIX_INLINE nixFloat4 ZZYY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 1); }
    static NIX_INLINE nixFloat4 ZZYZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 2); }
    static NIX_INLINE nixFloat4 ZZYW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 3); }
    static NIX_INLINE nixFloat4 ZZZX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 0); }
    static NIX_INLINE nixFloat4 ZZZY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 1); }
    static NIX_INLINE nixFloat4 ZZZZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 2); }
    static NIX_INLINE nixFloat4 ZZZW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 3); }
    static NIX_INLINE nixFloat4 ZZWX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 0); }
    static NIX_INLINE nixFloat4 ZZWY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 1); }
    static NIX_INLINE nixFloat4 ZZWZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 2); }
    static NIX_INLINE nixFloat4 ZZWW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 3); }
    static NIX_INLINE nixFloat4 ZWXX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 0); }
    static NIX_INLINE nixFloat4 ZWXY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 1); }
    static NIX_INLINE nixFloat4 ZWXZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 2); }
    static NIX_INLINE nixFloat4 ZWXW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 3); }
    static NIX_INLINE nixFloat4 ZWYX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 0); }
    static NIX_INLINE nixFloat4 ZWYY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 1); }
    static NIX_INLINE nixFloat4 ZWYZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 2); }
    static NIX_INLINE nixFloat4 ZWYW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 3); }
    static NIX_INLINE nixFloat4 ZWZX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 0); }
    static NIX_INLINE nixFloat4 ZWZY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 1); }
    static NIX_INLINE nixFloat4 ZWZZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 2); }
    static NIX_INLINE nixFloat4 ZWZW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 3); }
    static NIX_INLINE nixFloat4 ZWWX(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 0); }
    static NIX_INLINE nixFloat4 ZWWY(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 1); }
    static NIX_INLINE nixFloat4 ZWWZ(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 2); }
    static NIX_INLINE nixFloat4 ZWWW(const nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 3); }

    static NIX_INLINE nixFloat4 WXXX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 0); }
    static NIX_INLINE nixFloat4 WXXY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 1); }
    static NIX_INLINE nixFloat4 WXXZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 2); }
    static NIX_INLINE nixFloat4 WXXW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 3); }
    static NIX_INLINE nixFloat4 WXYX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 0); }
    static NIX_INLINE nixFloat4 WXYY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 1); }
    static NIX_INLINE nixFloat4 WXYZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 2); }
    static NIX_INLINE nixFloat4 WXYW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 3); }
    static NIX_INLINE nixFloat4 WXZX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 0); }
    static NIX_INLINE nixFloat4 WXZY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 1); }
    static NIX_INLINE nixFloat4 WXZZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 2); }
    static NIX_INLINE nixFloat4 WXZW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 3); }
    static NIX_INLINE nixFloat4 WXWX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 0); }
    static NIX_INLINE nixFloat4 WXWY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 1); }
    static NIX_INLINE nixFloat4 WXWZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 2); }
    static NIX_INLINE nixFloat4 WXWW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 3); }
    static NIX_INLINE nixFloat4 WYXX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 0); }
    static NIX_INLINE nixFloat4 WYXY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 1); }
    static NIX_INLINE nixFloat4 WYXZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 2); }
    static NIX_INLINE nixFloat4 WYXW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 3); }
    static NIX_INLINE nixFloat4 WYYX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 0); }
    static NIX_INLINE nixFloat4 WYYY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 1); }
    static NIX_INLINE nixFloat4 WYYZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 2); }
    static NIX_INLINE nixFloat4 WYYW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 3); }
    static NIX_INLINE nixFloat4 WYZX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 0); }
    static NIX_INLINE nixFloat4 WYZY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 1); }
    static NIX_INLINE nixFloat4 WYZZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 2); }
    static NIX_INLINE nixFloat4 WYZW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 3); }
    static NIX_INLINE nixFloat4 WYWX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 0); }
    static NIX_INLINE nixFloat4 WYWY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 1); }
    static NIX_INLINE nixFloat4 WYWZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 2); }
    static NIX_INLINE nixFloat4 WYWW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 3); }
    static NIX_INLINE nixFloat4 WZXX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 0); }
    static NIX_INLINE nixFloat4 WZXY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 1); }
    static NIX_INLINE nixFloat4 WZXZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 2); }
    static NIX_INLINE nixFloat4 WZXW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 3); }
    static NIX_INLINE nixFloat4 WZYX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 0); }
    static NIX_INLINE nixFloat4 WZYY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 1); }
    static NIX_INLINE nixFloat4 WZYZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 2); }
    static NIX_INLINE nixFloat4 WZYW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 3); }
    static NIX_INLINE nixFloat4 WZZX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 0); }
    static NIX_INLINE nixFloat4 WZZY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 1); }
    static NIX_INLINE nixFloat4 WZZZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 2); }
    static NIX_INLINE nixFloat4 WZZW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 3); }
    static NIX_INLINE nixFloat4 WZWX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 0); }
    static NIX_INLINE nixFloat4 WZWY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 1); }
    static NIX_INLINE nixFloat4 WZWZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 2); }
    static NIX_INLINE nixFloat4 WZWW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 3); }
    static NIX_INLINE nixFloat4 WWXX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 0); }
    static NIX_INLINE nixFloat4 WWXY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 1); }
    static NIX_INLINE nixFloat4 WWXZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 2); }
    static NIX_INLINE nixFloat4 WWXW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 3); }
    static NIX_INLINE nixFloat4 WWYX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 0); }
    static NIX_INLINE nixFloat4 WWYY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 1); }
    static NIX_INLINE nixFloat4 WWYZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 2); }
    static NIX_INLINE nixFloat4 WWYW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 3); }
    static NIX_INLINE nixFloat4 WWZX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 0); }
    static NIX_INLINE nixFloat4 WWZY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 1); }
    static NIX_INLINE nixFloat4 WWZZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 2); }
    static NIX_INLINE nixFloat4 WWZW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 3); }
    static NIX_INLINE nixFloat4 WWWX(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 0); }
    static NIX_INLINE nixFloat4 WWWY(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 1); }
    static NIX_INLINE nixFloat4 WWWZ(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 2); }
    static NIX_INLINE nixFloat4 WWWW(const nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 3); }
};


NIX_NAMESPACE_END