#pragma once

#include <time.h>

typedef struct {
  struct timespec start, end, target;
} UpdateTimer;

void set_target(UpdateTimer *ut, long seconds, long nanoseconds);

void get_current_time(struct timespec *ts);

void sleep_remaining(UpdateTimer *ut);