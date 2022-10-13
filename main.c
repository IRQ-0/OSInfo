#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sysinfoapi.h>
#include <time.h>
#include "osinfo.h"
#include "graph.h"

/*
Usage:

osinfo [args]

-without args = display everything once
-h = help
-r <milisecconds> = refresh cpu and mem info every number of milliseconds specified in parameter
-o <filename> = put output to file
-csv = (available only with -o option) set output format to csv
-t = (available only with -o and -r option) add time stamp (default off)
-g = show graph of cpu usage
*/

typedef struct {
	int refresh;
	int milis;
	int outputFile;
	int csvFormat;
	int timeStamp;
} params;

void displayHelp(void);
void displayEverything(FILE*);
void displayMemCpuRef(FILE*, params);
void displayGraph(void);
void getTime(FILE*);

int main(int argc, char *argv[]) {
	FILE *f;
	if (argc < 2) {
		displayEverything(stdout);
		return 0;
	} else if (argc == 2 && strcmp("-h", argv[1]) == 0) {
		displayHelp();
		return 0;
	} else {
		params p;
		p.outputFile = FALSE;
		p.csvFormat = FALSE;
		p.milis = 0;
		p.refresh = FALSE;
		p.timeStamp = FALSE;
		for (int i = 0; i < argc; i++) {
			if (strcmp("-csv", argv[i]) == 0) {
				if (p.outputFile != TRUE) {
					puts("Cannot set output format to csv, output file not specified");
					return 2;
				} else
					p.csvFormat = TRUE;
			} else if (strcmp("-t", argv[i]) == 0) {
				if (p.outputFile != TRUE) {
					puts("Cannot enable time stamp, output file not specified");
					return 2;
				} else
					p.timeStamp = TRUE;
			} else if (strcmp("-r", argv[i]) == 0) {
				p.refresh = TRUE;
				p.milis = atoi(argv[++i]);
				if (p.milis <= 0) {
					puts("Invalid refresh time");
					return 2;
				}
			} else if (strcmp("-o", argv[i]) == 0) {
				if (p.refresh != TRUE) {
					puts("Cannot set output to file, program is not in refresh mode");
					return 2;
				} else
					p.outputFile = TRUE;
				f = fopen(argv[++i], "wb");
				if (!f) {
					printf("Cannot create file %s\n", argv[i]);
					return 1;
				}
			} else if (strcmp("-g", argv[i]) == 0) {
				displayGraph();
			}
		}
		
		if (p.refresh) {
			if (p.outputFile) {
				displayMemCpuRef(f, p);
			} else {
				displayMemCpuRef(stdout, p);
			}
			
		}
	}
	
	return 0;
}

void displayGraph(void) {
	initGraph();
	for ( ; ; )
		putProc(getCpuLoad());
}

void getTime(FILE *f) {
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[1000];

  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
  	strcpy(buffer, asctime(timeinfo));
  	fwrite(buffer, 1, strlen(buffer) - 1, f);
}

void displayMemCpuRef(FILE* out, params p) {
	setOutputStream(out);
	
	if (!p.outputFile) {	
		system("cls");
		if (p.milis < 1000)
				puts("Warning: this program works better with values greater than 1000");
		fprintf(out, "OsInfo v1.0\n\n");
		fprintf(out, "Refreshing every %d ms\nPress CTRL+C to stop\n\n", p.milis);
	}

	if (p.outputFile && p.csvFormat) {
		if (p.timeStamp) {
			fputs("Time stamp, CPU Usage, Virtual mem usage, Physical mem usage\r\n", out);
		} else
			fputs("CPU Usage, Virtual mem usage, Physical mem usage\r\n", out);
	}
	
	while (1) {
		if (p.outputFile && p.csvFormat) {
			if (p.timeStamp) {
				getTime(out);
				fputc(',', out);
			}
			getCpuUsage();
			fputc(',', out);
			getUsedVirtualMemoryInProc();
			fputc(',', out);
			getUsedPhysicalMemoryInProc();
			fputs("\n", out);
		} else {
			fprintf(out, "Virtual memory usage:  ");
			getUsedVirtualMemory();
			fprintf(out, " out of " );
			getTotalVirtualMemory();
			fprintf(out, " equals ");
			getUsedVirtualMemoryInProc();
			fprintf(out, "\nPhysical memory usage: ");
			getUsedPhysicalMemory();
			fprintf(out, " out of ");
			getTotalPhysicalMemory();
			fprintf(out, " equals ");
			getUsedPhysicalMemoryInProc();
			fprintf(out, "\nCPU usage: ");
			getCpuUsage();
			fprintf(out, "\n");
			fflush(out);
			
			printf("\033[A\33[2KT\r");
			printf("\033[A\33[2KT\r");
			printf("\033[A\33[2KT\r");
		}
		Sleep(p.milis);
	}
}

void displayEverything(FILE* out) {
	setOutputStream(out);
	fprintf(out, "OsInfo v1.0\n\n");
	fprintf(out, "; MOTHERBOARD:\n");
	fprintf(out, "- Mother board name: ");
	getMotherBoardName();
	fprintf(out, "- Mother board version: ");
	getMotherBoardVersion();
	fprintf(out, "- Mother board manufacturer: ");
	getMotherBoardManufacturer();
	fprintf(out, "\n");
	
	fprintf(out, "; BIOS:\n");
	fprintf(out, "- Bios release date: ");
	getBiosReleaseDate();
	fprintf(out, "- Bios vendor: ");
	getBiosVendor();
	fprintf(out, "- Bios version: ");
	getBiosVersion();
	fprintf(out, "\n");
	
	fprintf(out, "; CPU:\n");
	fprintf(out, "- Cpu mhz: ");
	getCpuMhz();
	fprintf(out, "- Cpu name: ");
	getCpuName();
	fprintf(out, "- Cpu type: ");
	getCpuType();
	fprintf(out, "- Cpu cores: ");
	getCpuCores();
	fprintf(out, "- Cpu revision (this is no proper value, it will be fixed soon): ");
	getCpuRevision();
	fprintf(out, "- Cpu usage: ");
	getCpuUsage();
	fprintf(out, "\n\n");
	
	fprintf(out, "; MEMORY:\n");
	fprintf(out, "- Minimum allocation adress: ");
	getMinimumAllocationAdrress();
	fprintf(out, "- Maximum allocation adress: ");
	getMaximumAllocationAdrress();
	fprintf(out, "- Total virtual memory: ");
	getTotalVirtualMemory();
	fprintf(out, "\n- Total physical memory: ");
	getTotalPhysicalMemory();
	fprintf(out, "\n- Used virtual memory: ");
	getUsedVirtualMemory();
	fprintf(out, "\n- USed physical memory: ");
	getUsedPhysicalMemory();
}

void displayHelp(void) {
	puts("OsInfo v1.0\n");
	puts("Usage: osinfo [args]\n");
	puts("Without args = display everything once\n");
	
	puts("Args:");
	puts("-h = display help (display this)");
	puts("-r <milisecconds> = refresh cpu and mem info every number of milliseconds specified in parameter");
	puts("-o <filename> = put output to file");
	puts("-csv = (available only with -o option) set output format to csv");
	puts("-t = (available only with -o and -r option) add time stamp");
	puts("-g = show graph of cpu usage");
}
