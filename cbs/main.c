#define CONFIGURE_SCHEDULER_CBS
#include <rtems.h>
#include <rtems/cbs.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

void overrun_handler(rtems_cbs_server_id server_id) {
  printf("Budget overrun, fixing the task...\n");
  return;
}

// The main function for our tasks
rtems_task PeriodicTask(rtems_task_argument ignored) {
  rtems_id   rm_id;
  rtems_name rm_name = rtems_build_name('R', 'T', 'S', '0');
  rtems_cbs_server_id  server_id;
  rtems_cbs_parameters params;

  params.deadline = 100; // clock cycles
  params.budget   = 40;  // clock cycles

  rtems_cbs_initialize();
  rtems_cbs_create_server(&params, &overrun_handler, &server_id);
  rtems_cbs_attach_thread(server_id, RTEMS_SELF);
  check(rtems_rate_monotonic_create(rm_name, &rm_id), "failed to create monotonic period");

  uint16_t counter = 0;
  while (true) {
    if (rtems_rate_monotonic_period(rm_id, params.deadline) == RTEMS_TIMEOUT)
      break;
    
    /* Perform some periodic action */
    printf("PeriodicTask Activated! %d\n", counter++);
  }

  // missed the deadline, so clean up
  check(rtems_rate_monotonic_delete(rm_id), "failed to delete monotonic period");
  rtems_cbs_cleanup();
  exit(1);
}


// This Init function is the entrypoint to our RTEMS application.
rtems_task Init(rtems_task_argument ignored) {
  rtems_id task_id;
  rtems_name task_name = rtems_build_name('R', 'T', 'S', '0');

  check(create_task(task_name, 1, &task_id), "failed to create task");
  check(rtems_task_start(task_id, PeriodicTask, 0), "failed to start task");

  check(rtems_task_delete(RTEMS_SELF), "failed to delete self");
}
