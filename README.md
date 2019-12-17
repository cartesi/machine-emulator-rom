> :warning: The Cartesi team keeps working internally on the next version of this repository, following its regular development roadmap. Whenever there's a new version ready or important fix, these are published to the public source tree as new releases.

# Cartesi Machine Emulator ROM

The Cartesi Machine Emulator ROM is the reference software that boots a guest Operating System on the emulator.

## Getting Started

### Requirements

- RISCV64 C/C++ Compiler with support for C++17 (tested with GCC >= 8+).
- GNU Make >= 3.81
- Libfdt 1.4.7
- Docker image `cartesi/toolchain`

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

Thank you for your interest in Cartesi! Head over to our [Contributing Guidelines](CONTRIBUTING.md) for instructions on how to sign our Contributors Agreement and get started with Cartesi!

Please note we have a [Code of Conduct](CODE_OF_CONDUCT.md), please follow it in all your interactions with the project.

## Authors

* *Diego Nehab*
* *Victor Fusco*

## License

The machine-emulator-rom repository and all contributions are licensed under
[APACHE 2.0](https://www.apache.org/licenses/LICENSE-2.0). Please review our [LICENSE](LICENSE) file.
