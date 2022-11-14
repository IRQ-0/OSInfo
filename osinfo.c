#include "osinfo.h"

void regReadString(char* path, char* value, char* out) {
	HKEY key;
    DWORD type = REG_SZ;
    char buffer[BUFFER_SIZE];
    unsigned int len = sizeof(buffer);
    
    if (RegOpenKey(HKEY_LOCAL_MACHINE, path, &key)) {
    	return;
	}
    if (RegQueryValueEx(key, value, NULL, &type, (LPBYTE)&buffer, (LPDWORD)&len)) {
    	return;
	}
	
	strcpy(out, buffer);
}

DWORD regReadDword(char* path, char* value) {
	HKEY key;
    DWORD type = REG_DWORD;
    DWORD ret;
    unsigned int len = sizeof(ret);
    
    if (RegOpenKey(HKEY_LOCAL_MACHINE, path, &key)) {
    	return 0;
	}
    if (RegQueryValueEx(key, value, NULL, &type, (LPBYTE)&ret, (LPDWORD)&len)) {
    	return 0;
	}
	
	return ret;
}

void getUsedVirtualMemoryInProc(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	float used = (float)(meminfo.ullTotalPageFile - meminfo.ullAvailPageFile) / (1024*1024*1024);
	float total = (float)meminfo.ullTotalPageFile / (1024*1024*1024);
	fprintf(out, "%.2f%%", (used / total) * 100);
}

void getUsedPhysicalMemoryInProc(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	float used = (float)(meminfo.ullTotalPhys - meminfo.ullAvailPhys) / (1024*1024*1024);
	float total = (float)meminfo.ullTotalPhys / (1024*1024*1024);
	fprintf(out, "%.2f%%", (used / total) * 100);
}

void getCpuUsage(void) {
	fprintf(out, "%d%%", getCpuLoad());
}

void getCpuMhz(void) {
    fprintf(out, "%d\n", regReadDword("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "~Mhz"));
}

void setOutputStream(FILE* f) {
	out = f;
}

SYSTEM_INFO getSysBasicInfo(void) {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	
	return sysinfo;
}

void getCpuType(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	switch (sysinfo.dwProcessorType) {
		case PROCESSOR_INTEL_386:
			fprintf(out, "Intel 386");
			break;
			
		case PROCESSOR_INTEL_486:
			fprintf(out, "Intel 486");
			break;
			
		case PROCESSOR_INTEL_PENTIUM:
			fprintf(out, "Intel Pentium");
			break;
			
		case PROCESSOR_INTEL_IA64:
			fprintf(out, "IA-64");
			break;
			
		case PROCESSOR_AMD_X8664:
			fprintf(out, "x86-64");
			break;
			
		default:
			fprintf(out, "Unknown");
	}
	
	fprintf(out, "\n");
}

void getTotalVirtualMemory(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	fprintf(out, "%.2f Gb", (float)meminfo.ullTotalPageFile / (1024*1024*1024));
}

void getTotalPhysicalMemory(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	fprintf(out, "%.2f Gb", (float)meminfo.ullTotalPhys / (1024*1024*1024));
}

void getUsedVirtualMemory(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	fprintf(out, "%.2f Gb", (float)(meminfo.ullTotalPageFile - meminfo.ullAvailPageFile) / (1024*1024*1024));
}

void getUsedPhysicalMemory(void) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	fprintf(out, "%.2f Gb", (float)(meminfo.ullTotalPhys - meminfo.ullAvailPhys) / (1024*1024*1024));
}

void getPageSize(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	fprintf(out, "%d\n", sysinfo.dwPageSize);
}

void getMinimumAllocationAdrress(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	fprintf(out, "0x%.X\n", sysinfo.lpMinimumApplicationAddress);
}

void getCpuThreads(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	fprintf(out, "%d\n", sysinfo.dwNumberOfProcessors);
}

void getCpuRevision(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	fprintf(out, "%d\n", sysinfo.wProcessorRevision);
}

void getMaximumAllocationAdrress(void) {
	SYSTEM_INFO sysinfo = getSysBasicInfo();
	fprintf(out, "0x%.X\n", sysinfo.lpMaximumApplicationAddress);
}

void getCpuName(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}

void getMotherBoardManufacturer(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardManufacturer", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}

void getMotherBoardName(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardProduct", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
	
}

void getMotherBoardVersion(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardVersion", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}

void getBiosReleaseDate(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSReleaseDate", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}

void getBiosVendor(void) {
	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}

void getBiosVersion(void) {
 	char* buffer = malloc(BUFFER_SIZE * sizeof(char));
	regReadString("HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion", buffer);
	fprintf(out, "%s\n", buffer);
	free(buffer);
}
