#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 60
static char output_buffer[MAX_BUFFER];

double get_cpu_frequency() {
  double cpu_frequency = 0.0;
  FILE *file = fopen(("/proc/cpuinfo"), "r");
  if (file == ((void *)0)) {
    perror("Failed to open "
           "/proc/cpuinfo");
    exit(-1);
  }
  char line[128];
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "cpu MHz : %lf", &cpu_frequency);
  }
  fclose(file);

  return cpu_frequency;
}

void get_cpu_times(unsigned long long *idle, unsigned long long *total) {
  FILE *file;
  char line[128];

  file = fopen("/proc/stat", "r");
  if (file == NULL) {
    perror("Failed to open /proc/stat");
    return;
  }

  if (fgets(line, sizeof(line), file)) {
    unsigned long long user, nice, system, irq, softirq, steal, iowait;
    sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice,
           &system, idle, &iowait, &irq, &softirq, &steal);
    *total = user + nice + system + *idle + iowait + irq + softirq + steal;
  }

  fclose(file);
}

unsigned long long idle1 = 0;
unsigned long long total1 = 0;
double calculate_cpu_usage() {
  unsigned long long idle2, total2;
  double usage = 0.0;

  // Get the second set of CPU times
  get_cpu_times(&idle2, &total2);

  // Calculate the difference
  unsigned long long idle_diff = idle2 - idle1;
  unsigned long long total_diff = total2 - total1;

  if (total_diff != 0) {
    usage = (double)(total_diff - idle_diff) / (double)total_diff * 100.0;
  }

  idle1 = idle2;
  total1 = total2;

  return usage;
}

const char *cpu_freq(const char *fmt) {
  sprintf(output_buffer, fmt, get_cpu_frequency());
  return output_buffer;
}

const char *cpu_percentage(const char *fmt) {
  sprintf(output_buffer, fmt, calculate_cpu_usage());
  return output_buffer;
}
