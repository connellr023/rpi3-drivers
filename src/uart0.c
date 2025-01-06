#include "../include/uart0.h"
#include "../include/mbox.h"

void uart0_init() {
  uint32_t r;

  /* Initialize UART */
  *UART0_CR = 0; // Turn off UART0

  /* Set up clock for consistent divisor values */
  mbox_buffer[0] = 9 * 4;
  mbox_buffer[1] = MBOX_REQUEST;
  mbox_buffer[2] = MBOX_TAG_SETCLKRATE; // Set clock rate
  mbox_buffer[3] = 12;
  mbox_buffer[4] = 8;
  mbox_buffer[5] = 2;       // UART clock
  mbox_buffer[6] = 4000000; // 4Mhz
  mbox_buffer[7] = 0;       // Clear turbo
  mbox_buffer[8] = MBOX_TAG_LAST;

  mbox_call(MBOX_CH_PROP);

  /* Map UART0 to GPIO pins */
  r = *GPFSEL1;
  r &= ~((7 << 12) | (7 << 15)); // GPIO14, GPIO15
  r |= (4 << 12) | (4 << 15);    // ALT0

  *GPFSEL1 = r;
  *GPPUD = 0; // Enable pins 14 and 15

  r = 150;

  while (r--)
    asm volatile("nop");

  *GPPUDCLK0 = (1 << 14) | (1 << 15);
  r = 150;

  while (r--)
    asm volatile("nop");

  *GPPUDCLK0 = 0; // Flush GPIO setup

  *UART0_ICR = 0x7FF; // Clear interrupts
  *UART0_IBRD = 2;    // 115200 baud
  *UART0_FBRD = 0xB;
  *UART0_LCRH = 0x7 << 4; // 8n1, enable FIFOs
  *UART0_CR = 0x301;      // Enable Tx, Rx, UART
}

void uart0_send(uint32_t c) {
  const uint64_t max_attempts = 10000;
  uint64_t attempts = 0;

  /* Wait until we can send */
  do {
    asm volatile("nop");

    if (attempts++ >= max_attempts) {
      return;
    }
  } while (*UART0_FR & 0x20);

  /* Write the character to the buffer */
  *UART0_DR = c;
}

void uart0_puts(const char *s) {
  while (*s) {
    // Convert newline to carrige return + newline
    if (*s == '\n')
      uart0_send('\r');

    uart0_send(*s++);
  }
}

void uart0_hex(uint64_t d) {
  uint64_t n = 0;

  for (int c = 60; c >= 0; c -= 4) {
    // Get highest tetrad
    n = (d >> c) & 0xF;

    // 0-9 => '0'-'9', 10-15 => 'A'-'F'
    n += n > 9 ? 0x37 : 0x30;

    uart0_send(n);
  }
}