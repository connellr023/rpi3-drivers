pub extern fn uart0_init() void;
pub extern fn uart0_send(c: u32) void;
pub extern fn uart0_puts(s: [*:0]const u8) void;
pub extern fn uart0_hex(d: u64) void;
