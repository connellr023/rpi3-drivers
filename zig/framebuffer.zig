extern fn framebuffer_init() bool;

extern fn framebuffer_draw_pixel(x: u32, y: u32, color: u32) void;
extern fn framebuffer_fill_screen(color: u32) void;
extern fn framebuffer_draw_rect(x1: i32, y1: i32, x2: i32, y2: i32, color: u32, fill: bool) void;
