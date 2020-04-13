#include <rtems.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_TASKS 2

rtems_id task_ids[MAX_TASKS];
rtems_name task_names[MAX_TASKS];
uint16_t task_periods[MAX_TASKS];

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

// The main function for our tasks
rtems_task PeriodicTask(rtems_task_argument arg) {
  uint16_t period = task_periods[arg];

  printf("*** Starting periodic task %d with period %d ***\n", arg, period);

  while (true) {
    printf("Task: %d - Activated\n", arg);
    check(rtems_task_wake_after(period), "failed to wake after period");
  }
}

// This Init function is the entrypoint to our RTEMS application.
rtems_task Init(rtems_task_argument ignored) {
  printf("*** Initialising Tasks ***\n");

  task_names[0] = rtems_build_name('T', '0', ' ', ' ');
  task_names[1] = rtems_build_name('T', '1', ' ', ' ');
  task_periods[0] = 500;
  task_periods[1] = 1000;

  check(create_task(task_names[0], 1, &task_ids[0]), "failed to initialise task 0");
  check(create_task(task_names[1], 1, &task_ids[1]), "failed to initialise task 1");

  check(rtems_task_start(task_ids[0], PeriodicTask, 0), "failed to start task 0");
  check(rtems_task_start(task_ids[1], PeriodicTask, 1), "failed to start task 1");

  printf("*** Tasks running! ***\n");

  check(rtems_task_delete(RTEMS_SELF), "failed to delete init task");
}
