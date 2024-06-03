# Simple Status
Simple_status is a minimal C program to define how to build, and set a status message on window managers like [dwm](https://dwm.suckless.org/).
I developed this as a replacement for [slstatus](https://tools.suckless.org/slstatus/) since I was unhappy with the limitations and lack of documentation on how to use it.

You can define how to build your status in `simple_status.c`
```c title:simple_status.c
#include "simple_status.h"

// include what status components you want to use
// or create your own
#include "status_components/ram.h"
#include "status_components/cpu.h"
#include "status_components/time.h"

#define separator() then("  |  ")

// The only required function in this file is `build_status_msg`
int build_status_msg(string_builder *sb) {

  // I included a nice string_builder contextual macro... thing
  sb_start(sb);

    then(ram_percentage("ram perc: %.2f%%   "));
    then(ram_total("ram total: %.2f   "));
    then(ram_used("ram used: %.2f   "));

    separator();

    then(cpu_freq("MHz %0.2f  "));
    then(cpu_percentage("CPU %0.2f "));

    separator();

    then(time_date("%A, %B %d, %Y"));

  sb_end();

  return 0;
}
```

