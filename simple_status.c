
#include "simple_status.h"

#include "status_components/ram.h"

int build_status_msg(string_builder *sb) {

    sb_append(sb, ram_percentage("ram: %.2f%%"));

    return 0;
}