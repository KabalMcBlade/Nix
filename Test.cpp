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
    Vector asix(0.0f, 1.0f, 0.0f);
    nixFloat radians = 1.5708f; // 90 deg

    Quaternion rot(radians, asix);
    printf("Quaternion rot\n");
    printf("Axis: ");
    asix.Print3();
    printf("Radians: %f, Degree: %f\n", radians, NIX_RAD_TO_DEG(radians));
    printf("Quaternion output\n");
    rot.Print();
    rot.PrintClear();

    /*
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
    */


    Matrix mTSR(
        -0.75f, 0.0f, 0.65f, 0.0f,
        0.0f, 1.0f, .0f, 0.0f,
        -0.65f, 0.0f, -0.75f, 0.0f,
        10.0f, 10.0f, 20.0f, 1.0f);
    //Matrix mTsrOp(2.0f);

    Matrix mTsrOp(
        0.15f, 0.0f, -0.98f, 0.0f,
        0.0f, 1.0f, .0f, 0.0f,
        0.98f, 0.0f, 0.15f, 0.0f,
        2.0f, 2.0f, 5.0f, 1.0f);

    mTSR *= mTsrOp;
    mTSR /= mTsrOp;

    Matrix mTrans = mTSR.Transpose();

    Matrix mInvNoScale = mTSR.InverseNoScale();


    //////////////////////////////////////////////////////////////////////////

    Matrix mIdentity;
    Vector vTwice(2.0f);

    Vector r = vTwice * mTsrOp;

     
    getchar();

    return 0;
}

