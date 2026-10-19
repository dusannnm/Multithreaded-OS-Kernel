# RISC-V Operating System Kernel

A small educational operating-system kernel for the 64-bit RISC-V architecture. It is built around a freestanding C++ runtime, trap-based system calls, and a thread scheduler. The repository also includes C and C++ interfaces and selectable tests for the kernel features. Built for the course *Operating Systems* (srb. Operativni sistemi 1), School of Electrical Engineering, University of Belgrade.

## Features

- Memory allocation and deallocation, including free-space queries
- Thread creation, dispatch, joining, and thread IDs
- C and C++ thread APIs
- Semaphores, including timed and multi-unit operations
- Thread sleeping and timer-driven scheduling
- User-mode and supervisor-mode transitions
- Additional thread synchronization and resource tests

## Technologies

| Part | Technologies |
| --- | --- |
| Architecture | RISC-V 64-bit (`rv64ima`, `lp64`) |
| Languages | C, C++11, RISC-V assembly |
| Toolchain | RISC-V GNU GCC/binutils |
| Emulator | QEMU `qemu-system-riscv64` |
| Build | GNU Make |

## Requirements

- GNU Make
- A RISC-V 64-bit GCC and binutils toolchain (for example, `riscv64-unknown-elf-*`)
- QEMU with `qemu-system-riscv64`

The Makefile attempts to detect a supported RISC-V toolchain prefix automatically. If your tools use a different prefix or are not on `PATH`, set `TOOLPREFIX` when invoking `make`.

The Makefile uses Unix-style utilities such as `find`, `grep`, `sed`, and `rm`; on Windows, build and run it from WSL or another compatible Unix-like environment with the required toolchain and QEMU installed.

## Building and running

From the project root:

```sh
make
make qemu
```

The kernel starts in QEMU's console. When prompted, enter a two-digit test number from `01` to `11`, then press Enter. The test selection and implementation flags are in [`test/userMain.cpp`](test/userMain.cpp).

To remove generated build files:

```sh
make clean
```

## Tests

The test harness in `test/userMain.cpp` selects a test by its two-digit number:

| Test | Purpose |
| --- | --- |
| 01 | C API threads and synchronous context switching |
| 02 | C++ API threads and synchronous context switching |
| 03 | C API producer-consumer test with semaphores |
| 04 | C++ API producer-consumer test with semaphores |
| 05 | C API thread-sleep test |
| 06 | C++ API producer-consumer test with asynchronous context switching |
| 07 | Checks that user code runs in user mode; it is expected not to finish normally |
| 08 | Maximum thread count modification |
| 09 | Thread ID modification |
| 10 | Thread pairing modification |
| 11 | Resource modification |

Tests 01–07 are selected conditionally according to the `LEVEL_N_IMPLEMENTED` flags in `test/userMain.cpp`. The modification tests (08–11) are selected directly by the harness.

## Project structure

```text
.
├── h/                 Kernel and system-call interface headers
├── lib/               Hardware/memory headers and supplied libraries
├── src/               Kernel implementation and RISC-V assembly
├── test/              Test harness and feature tests
├── Makefile           Build, run, and clean targets
├── kernel.ld          RISC-V kernel linker script
└── .gdbinit.tmpl-riscv GDB configuration template for QEMU
```

The Makefile writes intermediate objects and dependency files under `build/`, and produces the `kernel` image and `kernel.asm` disassembly in the project root.

## Debugging

Start the kernel paused with the QEMU GDB stub:

```sh
make qemu-gdb
```

In a second terminal, start a RISC-V-capable GDB with the kernel image, then connect to the port printed by `make qemu-gdb`:

```sh
gdb-multiarch kernel
(gdb) target remote localhost:<port>
```

## License

This project includes modified xv6 software. See [`LICENSE`](LICENSE) for the copyright and license terms.


## Author

Dušan Milivojević, 2024/2025
