
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUFFER 60
static char output_buffer[MAX_BUFFER];

const char *time_date(const char *fmt) {
  // Get the current time
  time_t current_time = time(NULL);

  // Check if the time function failed
  if (current_time == ((time_t)-1)) {
    fprintf(stderr, "Failed to obtain the current time.\n");
    exit(-1);
  }

  struct tm *local_time = localtime(&current_time);
  if (strftime(output_buffer, sizeof(output_buffer), fmt, local_time) == 0) {
    fprintf(stderr, "Failed to format date.\n");
    exit(-1);
  }

  return output_buffer;
}
