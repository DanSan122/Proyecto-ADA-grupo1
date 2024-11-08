// Dll-ADA.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Dll-ADA.h"


// This is an example of an exported variable
DLLADA_API int nDllADA=0;

// This is an example of an exported function.
DLLADA_API int fnDllADA(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CDllADA::CDllADA()
{
    return;
}
