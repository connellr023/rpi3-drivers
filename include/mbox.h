/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 * Modified 2024 by connellr023@github
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef MBOX_HPP
#define MBOX_HPP

#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>

#define MBOX_REQUEST 0

/* channels */
#define MBOX_CH_POWER 0
#define MBOX_CH_FB 1
#define MBOX_CH_VUART 2
#define MBOX_CH_VCHIQ 3
#define MBOX_CH_LEDS 4
#define MBOX_CH_BTNS 5
#define MBOX_CH_TOUCH 6
#define MBOX_CH_COUNT 7
#define MBOX_CH_PROP 8

/* Tags */
#define MBOX_TAG_GETSERIAL 0x10004
#define MBOX_TAG_SETCLKRATE 0x38002
#define MBOX_TAG_LAST 0

#define VIDEOCORE_MBOX (MMIO_BASE + 0x0000B880)
#define MBOX_READ ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x0))
#define MBOX_POLL ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x10))
#define MBOX_SENDER ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x14))
#define MBOX_STATUS ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x18))
#define MBOX_CONFIG ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x1C))
#define MBOX_WRITE ((volatile uint32_t *)(VIDEOCORE_MBOX + 0x20))
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000

extern volatile uint32_t mbox_buffer[36];
extern bool mbox_call(uint8_t ch);

#endif // MBOX_HPP