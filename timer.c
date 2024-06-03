#include "timer.h"

#include <time.h>

#define CLOCK_MONOTONIC 1

void set_target(UpdateTimer *ut, long seconds, long nanoseconds) {
  ut->target.tv_sec = seconds;
  ut->target.tv_nsec = nanoseconds;
}

void get_current_time(struct timespec *ts) {
  clock_gettime(CLOCK_MONOTONIC, ts);
}

void sleep_remaining(UpdateTimer *ut) {
  long elapsed_ns =
      (ut->end.tv_sec - ut->start.tv_sec) * 1000000000L + (ut->end.tv_nsec - ut->start.tv_nsec);
  long remaining_ns = ut->target.tv_nsec - elapsed_ns;
  if (remaining_ns > 0) {
    struct timespec remaining;
    remaining.tv_sec = 0;
    remaining.tv_nsec = remaining_ns;
    nanosleep(&remaining, NULL);
  }
}