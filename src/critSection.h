#ifndef CRITSECT_H
#define CRITSECT_H

// Disable interrupts and returns the value in PRIMASK
extern int disableInterrupts(void);

extern void enableInterrupts(int i);

#endif
