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

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#define MBOX_TAG_SET_PHYS_WIDTH_HEIGHT 0x00048003
#define MBOX_TAG_SET_VIRT_WIDTH_HEIGHT 0x00048004
#define MBOX_TAG_SET_VIRT_OFFSET 0x00048004
#define MBOX_TAG_SET_COLOR_DEPTH 0x00048005
#define MBOX_TAG_SET_PIXEL_ORDER 0x00048006
#define MBOX_TAG_ALLOC_FRAMEBUFFER 0x00040001
#define MBOX_TAG_GET_PITCH 0x00040008

#define PIXEL_ORDER_RGB 1
#define PIXEL_ORDER_BGR 0

#define FB_WIDTH 800
#define FB_HEIGHT 480

#include <stdint.h>

namespace framebuffer {
constexpr uint32_t bgr_to_rgb(uint32_t color) {
  return ((color & 0xFF) << 16) | (color & 0xFF00) | ((color & 0xFF0000) >> 16);
}

bool init();

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void fill_screen(uint32_t color);
void draw_rect(int x1, int y1, int x2, int y2, uint32_t color,
               bool fill = true);
} // namespace framebuffer

#endif