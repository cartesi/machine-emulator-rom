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

Pull requests are welcome. When contributing to this repository, please first discuss the change you wish to make via issue, email, or any other method with the owners of this repository before making a change.

Please note we have a code of conduct, please follow it in all your interactions with the project.

## Authors

* *Diego Nehab*
* *Victor Fusco*

## License

The machine-emulator-rom repository and all contributions are licensed under
[APACHE 2.0](https://www.apache.org/licenses/LICENSE-2.0). Please review our [LICENSE](https://github.com/cartesi/machine-emulator-rom/blob/master/LICENSE) file.
