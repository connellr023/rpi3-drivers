#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "gpio.hpp"
#include <stdint.h>

#define TIMER_COUNTER_LOW ((volatile uint32_t *)(MMIO_BASE + 0x00003004))
#define TIMER_COUNTER_HIGH ((volatile uint32_t *)(MMIO_BASE + 0x00003008))

#define RAND_MAX 32767
#define RAND_MULTIPLIER 1103515245
#define RAND_INCREMENT 12345

namespace clock {
uint64_t current_micros();
uint64_t random_range(uint64_t min, uint64_t max);
} // namespace clock

#endif // CLOCK_HPP