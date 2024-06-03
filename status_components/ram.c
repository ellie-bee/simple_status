#include <stdio.h>
#include <stdlib.h>
#include "ram.h"

#define MAX_BUFFER 60

const char *ram_percentage(const char *fmt) {

  static char output_buffer[MAX_BUFFER];

    FILE *file;
    char line[128];
    unsigned long total = 0;
    unsigned long free = 0;
    unsigned long available = 0;
    unsigned long buffers = 0;
    unsigned long cached = 0;

    file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        exit(-1);
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %lu kB", &total) == 1 ||
            sscanf(line, "MemFree: %lu kB", &free) == 1 ||
            sscanf(line, "MemAvailable: %lu kB", &available) == 1 ||
            sscanf(line, "Buffers: %lu kB", &buffers) == 1 ||
            sscanf(line, "Cached: %lu kB", &cached) == 1) {
        }
    }

    fclose(file);

    if (total == 0) {
        fprintf(stderr, "Failed to read total memory from /proc/meminfo\n");
        exit(-1);
    }

    float used_percentage = 100.0f * (total - free - (buffers + cached)) / total;

  sprintf(output_buffer, fmt, used_percentage);

  return output_buffer;
}