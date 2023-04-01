#include "taskList.h"
#include "stdio.h"

/* Initialises a blank task list */
taskList_t tlInit(void) {
    // Initialise all values to 0
    taskList_t tl = {0};
    return tl;
}

/* Runs the next item in the task list.
 * Returns:
 * 0 on Success
 * 1 if no items remain in the task list.
 */
uint8_t tlRun(taskList_t * tl) {
    uint8_t nextTail = (tl->tail + 1) % 32;
    task_t toRun;
    if (tl->tail == tl->head) {
        // List is empty
        return 1;
    } else {
        // Run next task
        tl->tail = nextTail;
        toRun = tl->tasks[tl->tail];
        (toRun.taskPtr) (toRun.dataPtr);
        return 0;
    }
};

/* Adds an item to the task list
 * Parameters:
 * tl - The task list
 * taskPtr - A function pointer
 * dataPtr - a pointer that will be passed to taskPtr when run
 * Returns:
 * 0 on success
 * 1 if no room remains in the task list
 */
uint8_t tlAdd(taskList_t * tl, void (*taskPtr) (void * ), void * dataPtr) {
    uint8_t nextHead = (tl->head + 1) % 32;
    task_t toAdd;

    toAdd.taskPtr = taskPtr;
    toAdd.dataPtr = dataPtr;

    if(nextHead == tl->tail) {
        // List is full
        return 1;
    } else {
        // Add to list
        tl->head = nextHead;
        tl->tasks[nextHead] = toAdd;
        return 0;
    }
}
