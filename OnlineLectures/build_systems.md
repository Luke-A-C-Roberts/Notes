# Build Systems and Zig

Zig Build System & How to Build Software From Source - Andrew Kelley - GOTO 2023
(zig_build_systems)[https://www.youtube.com/watch?v=wFlyUzUVFhw]

## Make tips
- When using the make tool, it is best to first check `./config --help` for build details

- often when things are installed they are put into the default prefix `/usr/`. This is bad for source build programs, instead install to the prefix `~/local/`.

- `make` has bad defaults. `make -j <CPU cores>` is better because make by default uses a single cpu core.

- `sudo make install` should not be necessary if the default install prefix has been configured already.

- If `sudo` isn't used then make and install can be done together. `make && sudo make install` → `make install`.

- Use a release that makes sence not just some rando commit. Latest bugfix commits are good.

- Docker exists because people don't know how to build from source so don't use it.

- Dependancies can be a pain. sometimes it may also be necessary to build dependancies from source, if a distro doesn't support a certain version.

- Make helpful bug reports, include system details.

- make uses mtime-based caching, but it's a bit cracked.

## Zig build systems

Zig build just uses the language as a script.

- The system can be quite vercetile when testing different architectures. for example `zig build -Dtarget=aarch64-linux -fqemu -fsummary` compiles the program to 64-bit arch architecture and uses fqemu to test and fsummary to give build information.

- `./zig-cache/` contains files that show which files were needed during compilation of zig.

- `./build.zig.zon` contains external dependencies needed to compile the program by giving a URL and hash.
