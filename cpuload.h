#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float calculateCPULoad(unsigned long long, unsigned long long);
static unsigned long long fileTimeToInt64(const FILETIME);
int roundFloat(float);
int getCpuLoad(void);

#endif
