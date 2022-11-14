#ifndef OSINFO_H
#define OSINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <TCHAR.h>
#include <pdh.h>
#include "cpuload.h"

#define BUFFER_SIZE 1000

FILE* out;

// Output
void setOutputStream(FILE*);

// Motherboard
void getMotherBoardName(void);
void getMotherBoardVersion(void);
void getMotherBoardManufacturer(void);

// BIOS
void getBiosReleaseDate(void);
void getBiosVendor(void);
void getBiosVersion(void);

// CPU
void getCpuMhz(void);
void getCpuName(void);
void getCpuType(void);
void getCpuThreads();;
void getCpuRevision(void); // TODO: add proper print
void getCpuUsage(void); // without new line

// Memory
void getPageSize(void);
void getMinimumAllocationAdrress(void);
void getMaximumAllocationAdrress(void);
void getTotalVirtualMemory(void); // without new line char
void getTotalPhysicalMemory(void); // without new line char
void getUsedVirtualMemory(void); // without new line char
void getUsedPhysicalMemory(void); // without new line char
void getUsedVirtualMemoryInProc(void); // without new line char
void getUsedPhysicalMemoryInProc(void); // without new line char

// Don't use this by yourself unless you know how to
void regReadString(char*, char*, char*);
DWORD regReadDword(char*, char*);
SYSTEM_INFO getSysBasicInfo(void);
static float calculateCPULoad();
static unsigned long long fileTimeToInt64();

#endif
