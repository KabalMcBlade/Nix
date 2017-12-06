// Nix.cpp : Defines the entry point for the console application.
//

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

/*
To set this compiler option for AVX, AVX2, IA32, SSE, or SSE2 in Visual Studio

1. Open the Property Pages dialog box for the project. For more information, see How to: Open Project Property Pages.
2. Select the Configuration Properties, C/C++ folder.
3. Select the Code Generation property page.
4. Modify the Enable Enhanced Instruction Set property.

//////////////////////////////////////////////////////////////////////////

Or by Arguments

/arch:IA32
Specifies no enhanced instructions and also specifies x87 for floating-point calculations.

/arch:SSE
Enables the use of SSE instructions.

/arch:SSE2
Enables the use of SSE2 instructions. This is the default instruction on x86 platforms if no /arch option is specified.

/arch:AVX
Enables the use of Intel Advanced Vector Extensions instructions.

/arch:AVX2
Enables the use of Intel Advanced Vector Extensions 2 instructions.

//////////////////////////////////////////////////////////////////////////

This solution has set /arch:AVX2 just to set the Test.cpp included
*/

#include "Nix/Nix.h"

NIX_OPTIMIZATION_OFF

NIX_USING_NAMESPACE

int main()
{
    Vector a(1.0f, 2.0f, 3.0f, 4.0f);
    Vector b(6.0f, 7.0f, 8.0f, 9.0f);

    printf("Cross product\n");

    printf("\nPrint Vectors\n");
    a.Print();
    b.Print();

    printf("\nResut\n");
    Vector res = a.Cross(b);
    res.Print();

    printf("\nLengths\n");
    Vector la = a.Length();
    Vector lb = b.Length();
    la.Print();
    lb.Print();

    printf("\nLengths\n");
    Vector la3 = a.Length3();
    Vector lb3 = b.Length3();
    la3.Print();
    lb3.Print();

    getchar();

    return 0;
}

