/*
 * Simple RTEMS configuration
 */
#include <rtems.h>

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MICROSECONDS_PER_TICK  1000
#define CONFIGURE_MAXIMUM_TASKS          3
#define CONFIGURE_MAXIMUM_PERIODS        1

#define CONFIGURE_SCHEDULER_CBS

#define CONFIGURE_INIT

#include <rtems/cbs.h>
#include <rtems/confdefs.h>
#include <rtems/scheduler.h>
