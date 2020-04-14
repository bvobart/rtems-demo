// heavily inspired by: https://docs.rtems.org/branches/master/c-user/rate_monotonic_manager.html#simple-periodic-task
#include <rtems.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_PERIOD 100

// Checks whether the status code indicates success, exits with error otherwise.
void check(rtems_status_code status, char * message) {
  if (status != RTEMS_SUCCESSFUL) {
    printf("ERROR: Received status %d, message: %s\n", status, message);
    exit(1);
  }
}

// Syntactic sugar to create a task with default stack size, default modes and default attributes.
rtems_status_code create_task(rtems_name name, rtems_task_priority prio, rtems_id *id) {
  return rtems_task_create(name, prio, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, id);
}

// The main function for our periodic task
rtems_task PeriodicTask(rtems_task_argument ignored) {
  rtems_id period_id;
  rtems_name period_name = rtems_build_name('P', 'E', 'R', 'D');
  uint16_t counter = 0;

  check(rtems_rate_monotonic_create(period_name, &period_id), "failed to create monotonic period");

  while (true) {
    if (rtems_rate_monotonic_period(period_id, DEFAULT_PERIOD) == RTEMS_TIMEOUT)
      break;
    
    /* Perform some periodic actions */
    printf("PeriodicTask Activated! %d\n", counter++);
  }

  /* missed deadline so delete period and self */
  printf("PeriodicTask missed its deadline!");
  check(rtems_rate_monotonic_delete(period_id), "failed to delete period on task");
  check(rtems_task_delete(RTEMS_SELF), "failed to delete self");
}

// This Init function is the entrypoint to our RTEMS application.
rtems_task Init(rtems_task_argument ignored) {
  rtems_id task_id;
  rtems_name task_name = rtems_build_name('R', 'T', 'S', '0');

  check(create_task(task_name, 1, &task_id), "failed to create task");
  check(rtems_task_start(task_id, PeriodicTask, 0), "failed to start task");

  check(rtems_task_delete(RTEMS_SELF), "failed to delete self");
}
