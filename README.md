# Nix
Tiny optimized math framework game oriented

> Nix is an ancient greek word means Darkness.

This would be a tiny math library for game purpose (just to be clear, the inverse of the matrix would be game oriented, with the 3x3 describes rotation and scaling and the 4th lane the translation, and not a generic transform)

It implement SSE2, SSE3, SSSE3, SSE4, SSE4.2 and AVX and AVX2

I had started to implement also the AVX512, for the skylake subset, but I'm unable to test it, hence I leave that for a next implementation.

Now I'm bored to implement this library without any purpose. Hence I'm going to stop the developening of this and start a project that actually using this.

> Why I did such effort?
> The answer is easy: I want a lightweight math library with low overhead, with NO vtable call, optimized as good as I need, full SIMD (no scalar) and easy to use.


# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2015) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabal2013/Nix?branch=master&svg=true)](https://ci.appveyor.com/project/Kabal2013/Nix) |


# License

```
// Copyright 2017 Michele Condo'
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
```