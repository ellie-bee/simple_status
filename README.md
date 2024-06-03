# Simple Status
Simple_status is a minimal C program to define how to build, and set a status message on window managers like [dwm](https://dwm.suckless.org/).
I developed this as a replacement for [slstatus](https://tools.suckless.org/slstatus/) since I was unhappy with the limitations and lack of documentation on how to use it.

You can define how to build your status in `simple_status.c`
```c title:simple_status.c
#include "simple_status.h"
// include what status components you want to use
// or create your own
#include "status_components/ram.h"
#include "status_components/time.h"
#include "status_components/host.h"

// define real functions 
void separate(string_builder *sb) {
  sb_append(sb, " | ");
}

// The only required function in this file is `build_status`
int build_status(string_builder *sb) {
  sb_append(sb, hostname("Hostname: %s"));
  separate(sb);
  sb_append(sb, cpu_percentage("cpu: %.2f%%"));
  sb_append(sb, ram_percentage("ram: %.2f%%"));
  separate(sb);
  sb_append(sb, date("%s"));
  sb_append(sb, time("%s"));
  return 0;
}
```

Once you're happy with your configuration you can `make install`.

