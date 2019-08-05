# Cartesi Machine Emulator ROM

The Cartesi Machine Emulator ROM is the reference software that boots a guest Operating System on the emulator.

## Getting Started

### Requirements

- RISCV64 C/C++ Compiler with support for C++17 (tested with GCC >= 8+).
- GNU Make >= 3.81
- Libfdt 1.4.7
- Docker image cartesi/toolchain-env:v1

### Build

```bash
$ make downloads 
$ make toolchain-env
[toolchain-env]$ make dep
[toolchain-env]$ make
[toolchain-env]$ exit 
```

Cleaning:

```bash
[toolchain-env]$ make depclean
[toolchain-env]$ make clean
```

## Usage

The file `build/rom.bin` is the compiled ROM code that can be used with the emulator.

## Contributing

Thank you for your interest in Cartesi! Head over to our [Contributing Guidelines](https://github.com/cartesi/machine-emulator-rom/blob/Add-Contributing-Agreement/CONTRIBUTING.md) for instructions on how to sign our Contributors Agreement and get started with Cartesi!

Please note we have a code of conduct, please follow it in all your interactions with the project.

## Authors

* *Diego Nehab*
* *Victor Fusco*

## License

- TODO
