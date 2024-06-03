#include <stdlib.h>

#include "display.h"
#include "simple_status.h"
#include "timer.h"

int main() {
  Display *display = get_display();

  UpdateTimer ut = {0};

  string_builder sb = {0};
  sb_init(&sb, 256);

  while(1) {
    // set the target time for an update frame
    // 1E9 - once  per second
    set_target(&ut, 0, 1E9);

    // get the start time of the current frame
    get_current_time(&ut.start);

    // defined in `simple_status.c`
    build_status_msg(&sb);
    display_status(display, sb.str);

    // empty the string_builder to save on mallocs
    sb_empty(&sb);

    // sleep until the next frame
    get_current_time(&ut.end);
    sleep_remaining(&ut);
  }

  // cleanup
  free(sb.str);
  free_display(display);

  exit(0);
}
