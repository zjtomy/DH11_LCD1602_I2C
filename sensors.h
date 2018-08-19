#ifndef SENSORS_H_
#define SENSORS_H_
#include <inttypes.h>

#define TMR0_MSK (TCNT0/2)

void DH11_init(void);
void DH11_read(uint8_t *bits_timing);

#endif
