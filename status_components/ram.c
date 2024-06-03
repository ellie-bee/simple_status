#include "ram.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 60
static char output_buffer[MAX_BUFFER];

static unsigned long total_mem;
static unsigned long free_mem;
static unsigned long available_mem;
static unsigned long buffers_mem;
static unsigned long cached_mem;

void get_ram_info() {
  FILE *file = fopen(("/proc/meminfo"), "r");
  if (file == ((void *)0)) {
    perror("Failed to open "
           "/proc/meminfo");
    exit(-1);
  }
  char line[128];
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "MemTotal: %lu kB", &total_mem);
    sscanf(line, "MemFree: %lu kB", &free_mem);
    sscanf(line, "MemAvailable: %lu kB", &available_mem);
    sscanf(line, "Buffers: %lu kB", &buffers_mem);
    sscanf(line, "Cached: %lu kB", &cached_mem);
  }
  fclose(file);

  if (total_mem == 0) {
    fprintf(stderr, "Failed to read total memory from /proc/meminfo\n");
    exit(-1);
  }
}

const char *ram_percentage(const char *fmt) {
  get_ram_info();
  sprintf(output_buffer, fmt,
          100.0f * (total_mem - free_mem - (buffers_mem + cached_mem)) /
              total_mem);
  return output_buffer;
}

const char *ram_total(const char *fmt) {
  get_ram_info();
  sprintf(output_buffer, fmt, total_mem / 1E6);
  return output_buffer;
}

const char *ram_used(const char *fmt) {
  get_ram_info();
  sprintf(output_buffer, fmt,
          (total_mem - free_mem - (buffers_mem + cached_mem)) / 1E6);
  return output_buffer;
}