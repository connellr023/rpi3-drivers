#include "mbox.hpp"

/* mailbox message buffer */
alignas(16) volatile uint32_t mbox::buffer[36];

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox::call(uint8_t ch) {
  uint32_t r = (((uint32_t)((unsigned long)&mbox::buffer) & ~0xF) | (ch & 0xF));

  /* wait until we can write to the mailbox */
  do {
    asm volatile("nop");
  } while (*MBOX_STATUS & MBOX_FULL);

  /* write the address of our message to the mailbox with channel identifier */
  *MBOX_WRITE = r;

  /* now wait for the response */
  while (1) {
    /* is there a response? */
    do {
      asm volatile("nop");
    } while (*MBOX_STATUS & MBOX_EMPTY);

    /* is it a response to our message? */
    if (r == *MBOX_READ)
      /* is it a valid successful response? */
      return mbox::buffer[1] == MBOX_RESPONSE;
  }

  return 0;
}