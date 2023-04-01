#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/sync.h"

#include "taskList.h"

taskList_t tl;

void sampleTask(void * data);

bool slowIRQ(repeating_timer_t *rt);
bool fastIRQ(repeating_timer_t *rt);

int main(void) {
    stdio_init_all();
    sleep_ms(10000);
    repeating_timer_t fastTimer;
    repeating_timer_t slowTimer;
    add_repeating_timer_us(100 * 1000, fastIRQ, NULL, &fastTimer);
    add_repeating_timer_us(1000 * 1000, slowIRQ, NULL, &slowTimer);

    tl = tlInit();

    while (true) {
        tlRun(&tl);
    }
}

bool slowIRQ(repeating_timer_t *rt) {
    tlAdd(&tl, sampleTask, "Hello world!");
    return true;
}

bool fastIRQ(repeating_timer_t *rt) {
    tlAdd(&tl, sampleTask, "Fast!");
    return true;
}

/* A simple test task that prints a string (passed by reference) and
 * the locations of the head and tail. */
void sampleTask(void * data) {
    // This'd probably work really well with a memory pool.
    char * str = data;

    printf("%s, Head: %d, Tail: %d\n", str, tl.head, tl.tail);
}
