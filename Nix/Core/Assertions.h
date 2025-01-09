// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Core\Assertions.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once

#include <cstdio>
#include <assert.h>     // for assert


#include "BasicDefines.h"


#ifdef _DEBUG

#define nixAssert( condition, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
    }
#define nixAssertVoid( condition, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		return; \
    }
#define nixAssertValue( condition, return_value, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		return return_value; \
    }

#else

#define nixAssert( condition, format, ... )
#define nixAssertVoid( condition, format, ... )
#define nixAssertValue( condition, return_value, format, ... )

#endif 


#define nixAssertReturnVoid( condition, format, ... )					nixAssertVoid( condition, format, __VA_ARGS__ )
#define nixAssertReturnValue( condition, return_value, format, ...  )	nixAssertValue( condition, return_value, format, __VA_ARGS__ )