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
    Vector a4(1.0f, 2.0f, 3.0f, 4.0f);
    Vector b4(6.0f, 7.0f, 8.0f, 9.0f);
    Vector res4 = a4.GetDot(b4);

    printf("Dot Result (4 elements and dot of 4 elements)\n");
    printf("\nPrint3\n");

    a4.Print3();
    b4.Print3();
    res4.Print3();

    printf("\nPrint4\n");

    a4.Print();
    b4.Print();
    res4.Print();

    printf("\n================================\n");
    
    Vector a3(1.0f, 2.0f, 3.0f);
    Vector b3(7.0f, 8.0f, 9.0f);
    Vector res3 = a3.GetDot(b3);

    printf("\nDot Result (3 elements and dot of 4 elements)\n");
    printf("\nPrint3\n");

    a3.Print3();
    b3.Print3();
    res3.Print3();

    printf("\nPrint4\n");

    a3.Print();
    b3.Print();
    res3.Print();
    
    printf("\n================================\n");
    
    Vector a3f(1.0f, 2.0f, 3.0f);
    Vector b3f(7.0f, 8.0f, 9.0f);
    Vector res3f = a3f.GetDot3(b3f);

    printf("\nDot Result (3 elements and dot of 3 elements)\n");
    printf("\nPrint3\n");

    a3f.Print3();
    b3f.Print3();
    res3f.Print3();

    printf("\nPrint4\n");

    a3f.Print();
    b3f.Print();
    res3f.Print();

    printf("\n================================\n");

    // here the result expected is right (44) even if we're looking for 50, 
    // just because we forgotten that in this case the second vector resulting in 6,7,8 and NOT as the before 7,8,9
    Vector a4f(1.0f, 2.0f, 3.0f, 4.0f);
    Vector b4f(6.0f, 7.0f, 8.0f, 9.0f);
    Vector res4f = a4f.GetDot3(b4f);

    printf("\nDot Result (4 elements and dot of 3 elements)\n");
    printf("\nPrint3\n");

    a4f.Print3();
    b4f.Print3();
    res4f.Print3();

    printf("\nPrint4\n");

    a4f.Print();
    b4f.Print();
    res4f.Print();

    getchar();

    return 0;
}

