
#include "simple_status.h"

#include "status_components/ram.h"
#include "status_components/cpu.h"
#include "status_components/time.h"

#define separator() then("  |  ")

int build_status_msg(string_builder *sb) {

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


