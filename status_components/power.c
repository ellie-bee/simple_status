#include "power.h"
#include <stdio.h>

#define MAX_BUFFER_LEN 128
static char output_buffer[MAX_BUFFER_LEN];
/*

Since POWER_SUPPLY_CURRENT_NOW is in µA and POWER_SUPPLY_CHARGE_ are all in µAh
then,

(POWER_SUPPLY_CHARGE_FULL - POWER_SUPPLY_CHARGE_NOW) / POWER_SUPPLY_CURRENT_NOW

will calculate the time in hours to reach POWER_SUPPLY_CHARGE_FULL, assuming
that POWER_SUPPLY_CURRENT_NOW remains constant.

/sys/class/power_supply/{BAT0}/uevent
    POWER_SUPPLY_STATUS=(Discharging|Charging|Full)
    POWER_SUPPLY_VOLTAGE_NOW=17415000
    POWER_SUPPLY_ENERGY_FULL=80900000
    POWER_SUPPLY_ENERGY_NOW=80900000
    POWER_SUPPLY_CAPACITY=100
*/

char status[12] = "";
unsigned long long capacity = 0;
unsigned long long energy_full = 0;
unsigned long long energy_now = 0;

void get_battery_info(const char *battery) {
  char line_buffer[120];
  sprintf(line_buffer, "/sys/class/power_supply/%s/uevent", battery);
  FILE *file = fopen(line_buffer, "r");
  while (fgets(line_buffer, sizeof(line_buffer), file)) {
    sscanf(line_buffer, "POWER_SUPPLY_STATUS=%s\n", status);
    sscanf(line_buffer, "POWER_SUPPLY_ENERGY_FULL=%llu", &energy_full);
    sscanf(line_buffer, "POWER_SUPPLY_ENERGY_NOW=%llu", &energy_now);
    sscanf(line_buffer, "POWER_SUPPLY_CAPACITY=%llu", &capacity);
  }
  fclose(file);
}

const char *battery_percent(const char *battery_id, const char *fmt) {
  get_battery_info(battery_id);

  sprintf(output_buffer, fmt, (int)capacity);

  return output_buffer;
}

const char *battery_rate(const char *battery_id) {
  unsigned long long energy_then = energy_now;
  get_battery_info(battery_id);

  return NULL;
}

const char *charging_state(const char *battery_id, const char *fmt) {
  get_battery_info(battery_id);

  return status;
};