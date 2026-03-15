#ifndef __CLOCK_H__
#define __CLOCK_H__
// Reference Manual Section 6 p.95-137

// Enables or disables clock with specific state
void clock_set(uint32_t reg, uint32_t clock, uint32_t state);

#endif