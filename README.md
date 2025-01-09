# Nix
Tiny math framework game oriented

> Nix is an ancient greek word means Darkness.

This would be a tiny math library for game purpose.

It implements **almost** everything in SSE2. So the Vector, Matrix and Quaternion are rapresented as _m128 line.
Some of the functions used, whenever possible, are using SSE3, SSSE3 and SSE4 for optimization purpose.


`NOTE: I made this library to learn a bit more and to try to add math functions in SIMD, so if there are some bugs, well you are advised!`


> There are plenty of math library around the web, so why I did such effort?
> The answer is easy: I want to learn a bit more on SIMD and I want also a easy, lightweight and optimized math library.


## LICENSE

- Sources:
	- **NIX**, the main project, is under MIT License
	- **sse_mathfun.h** is under zlib License



# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2017) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabalmcblade/Nix?branch=master&svg=true)](https://ci.appveyor.com/project/kabalmcblade/Nix) |
