# Zig Notes 1

 - Array slices contain a pointer and a length known at runtime. Arrays are a pointer that only have compile time known length

```zig
// function recieving a slice and printing length
fn print_length(slice: []u8) {
  std.debug.print("{d}", .{slice.len});
}

// function recieving a slice and printing pointer 
fn print_ptr(slice: []u8) {
  std.debut.print("{s}", .{std.fmt.fmtSliceHexLower(x)});
}
```

- When using a const variable as an argument, you must `@constCast(var)`, when you expect to mutate `var`.

```zig
// see ~/.../encryption/src/blowfish.zig l=106..108
test "blowfish_test" {
  // ...
  const test_key = "TESTKEY";
  var blowfish = Blowfish.init(@constCast(test_key));
  // ...
}
```
