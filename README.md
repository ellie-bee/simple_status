# Simple Status
Simple_status is a minimal C program to build and set a status message on window managers like [dwm](https://dwm.suckless.org/).
I developed this as a replacement for [slstatus](https://tools.suckless.org/slstatus/) since I was unhappy with the limitations and lack of documentation on how to use it.

You can define how to build your status in `simple_status.c`
```c title:simple_status.c
#include "simple_status.h"

#include "status_components/cpu.h"
#include "status_components/power.h"
#include "status_components/ram.h"
#include "status_components/time.h"

#include "string_builder.h"

// they're all just strings
const char *separator = "  |  ";

// build up small parts into larger
const char *cpu_and_ram() {
  string_builder sb = sb_new();
  sb_init(&sb, 256);

  sb_append(&sb,
    cpu_percentage("CPU %0.2f%% "),
    "  ",
    ram_percentage("RAM %.2f%%"));
  
  return sb_build(&sb);
}

// build_status_msg should return your completed status message
int build_status_msg(string_builder *sb) {

  // use your favorite tools to build it up
  sb_sep_by(sb, separator,
    battery_percent("BAT0", "battery: %d%%"),
    cpu_and_ram(),
    time_date("%A, %B %d, %Y  %H:%M"));

  return 0;
}
```

