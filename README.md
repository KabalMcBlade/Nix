# Nix
Tiny optimized math framework game oriented

> Nix is an ancient greek word means Darkness.

This would be a tiny math library for game purpose ONLY.
To be clear the inverse of the matrix describes a 3x3 rotation and scaling, the 4th lane the translation: this means that if you are using for generic purpose, the results will be wrong!

It implements everything in SSE2. So the Vector, Matrix and Quaternion are rapresented as _m128 line.
Some of the functions used, whenever possible, are using SSE3, SSSE3, SSE4, SSE4.2, AVX and AVX2 for optimization purpose.
I skipped the AVX512 skylake subset because I don't have the proper CPU to test.


`NOTE: I made this library to learn a bit more and to try to add math functions in SIMD, so if there are some bugs, well you are advised!`


> Why I did such effort?
> The answer is easy: I want to learn a bit more on SIMD and I want also a lightweight math library with low overhead, with no vtable call, optimized as good as I need, full SIMD (no scalar) and easy to use.


# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2015) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabalmcblade/Nix?branch=master&svg=true)](https://ci.appveyor.com/project/kabalmcblade/Nix) |
