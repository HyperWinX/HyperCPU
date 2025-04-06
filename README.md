<div align="center">
     <picture>
          <source media="(prefers-color-scheme: dark)" srcset="images/logo_dark.png">
          <source media="(prefers-color-scheme: light)" srcset="images/logo.png">
          <img alt="HyperCPU" src="images/logo.png">
     </picture>
</div>

<h4 align="center">The <i>hyper</i> toolkit for custom <i>hyper</i> ISA.</h4>

<p align="center">
     <a href="https://github.com/HyperWinX/HyperCPU/issues">
     <img src="https://img.shields.io/github/issues/HyperWinX/HyperCPU"
          alt="GitHub opened issues"></a>
     <img src="https://img.shields.io/badge/version-0.4.5-red"
          alt="Version">
     <img src="https://img.shields.io/github/actions/workflow/status/HyperWinX/HyperCPU/testing.yml?branch=dev"
          alt="CI status">
     <img src="https://img.shields.io/badge/status-in_development-red"
          alt="Status">
     <img src="https://img.shields.io/github/license/HyperWinX/HyperCPU"
          alt="License">
     <img src="https://img.shields.io/github/stars/HyperWinX/HyperCPU?color=lime"
          alt="Stars">
</p>

>[!IMPORTANT]
> HyperCPU is almost ready for use! Wait for 1.0 release to try it out or build the project yourself, test and report found issues.

<img alt="HyperCPU screenshot" src="images/screenshot.png">

HyperCPU is a set of programs created to work with my own simple ISA (instruction set architecture). The project was created for fun, but it took a lot of time (and nerves) and I learned a lot while working on it.

HyperCPU project includes:
* **hCPU emulator**;
* **hASM assembler**;
* ~~**hASM disassembler**~~ (planned).

The project roadmap can be found [here](ROADMAP.md).

### Installation

>[!WARNING]
> HyperCPU supports 64-bit GNU/Linux systems only. It is known to be successfully built and running on `amd64` and `aarch64` architectures.

#### Dependencies

* `gcc >= 12` or `clang >= 14`;
* `cmake >= 3.25`;
* `make`;
* `ninja`;
* `re2`;
* `fmt`;
* `googletest` (required for building tests in Release profile);
* `python3`, `python3-pip`, `python3-sphinx`, `python3-sphinx-rtd-theme` (required for building a documentation).

#### Build instructions

```bash
$ git clone https://github.com/HyperWinX/HyperCPU --recursive
$ cd HyperCPU
$ cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
$ make -C build default -j$(nproc)
```

`cmake` build options (use `-D` flag to define them):

* `CMAKE_BUILD_TYPE:STRING` - project build profile (`Release`, `RelWithDebInfo` or `Debug`), mandatory to be specified;

The compiled binaries should be located in `build` directory. The generated documentation should be located in `docs/_build/html` directory. After building the project open `index.html` file and start reading the documentation.

Do not forget to check out [examples](examples) folder for interesting code examples that will help you better understand the syntax of hASM and the power of HyperCPU.

#### Advanced building
HyperCPU build system supports multiple flags to customize the building process. For example:

* `HCPU_COMPILER:STRING` - allows to select compiler. Possible modes:
    * `auto` - don't do anything. Use CMake autodetection or passed compiler paths.
    * `clang` - searches for `clang` and `clang++` binaries. Supports hinting, so, for example, if `clang` binary is called `clang-19`, you can pass: `-DHCPU_COMPILER=clang -DCMAKE_C_COMPILER=clang-19`.
    * `gcc` - searches for gcc and g++ binaries. Be careful, in some environments Clang can do gcc -> clang symlinks. You can hint the binary name the same was as with clang mode: `-DHCPU_COMPILER=gcc -DCMAKE_C_COMPILER=gcc-14`.
* `HCPU_LTO:BOOL` - enable building with LTO. If Clang is used, searches for LLD. If LLD is found, LTO will be enabled, otherwise LTO will be unavailable. In case of GCC there are no dependencies.
* `HCPU_MARCH_NATIVE:BOOL` - use -march=native flag.
* `HCPU_SANITIZERS:BOOL` - set to OFF if you want to disable ASan and LSan, otherwise it will be enabled.

### Usage

#### `hcasm` (hASM assembler)

To compile a program to a binary file:

```bash
$ ./hcasm -o <target> <source>
```

To compile a program to an object file:

```bash
$ ./hcasm -c <target> <source>
```

To do things with a different verbosity level (`debug`, `info`, `warning`, `error`):

```bash
$ ./hcasm -v <verbosity_level> ...
```

To display help message and exit:

```bash
$ ./hcasm -h # = ./hcasm --help
```

To display program version and exit:

```bash
$ ./hcasm --version
```

#### `hcemul` (hCPU emulator)

To run a binary:

```bash
$ ./hcasm <target>
```

To do things with a different verbosity level (`debug`, `info`, `warning`, `error`):

```bash
$ ./hcemul -v <verbosity_level> ...
```

To display help message and exit:

```bash
$ ./hcemul -h # = ./hcemul --help
```

To display program version and exit:

```bash
$ ./hcemul --version
```

### Build status
## Supported Distributions

| Distribution    | Build Status |
|-----------------|--------------|
| Fedora          | [![Fedora Build Status](https://img.shields.io/github/actions/workflow/status/HyperWinX/HyperCPU/distro-ci.yml?label=Fedora&jobName=Build-Fedora)](https://github.com/HyperWinX/HyperCPU/actions/workflows/distro-ci.yml) |
| Debian Stable   | [![Debian Stable Build Status](https://img.shields.io/github/actions/workflow/status/HyperWinX/HyperCPU/distro-ci.yml?label=Debian%20Stable&jobName=Build-Debian-Stable)](https://github.com/HyperWinX/HyperCPU/actions/workflows/distro-ci.yml) |
| Debian Unstable | [![Debian Unstable Build Status](https://img.shields.io/github/actions/workflow/status/HyperWinX/HyperCPU/distro-ci.yml?label=Debian%20Unstable&jobName=Build-Debian-Unstable)](https://github.com/HyperWinX/HyperCPU/actions/workflows/distro-ci.yml) |

### Contributing

HyperCPU is in active development and we will be happy to hear any feedback from you. Do not hesitate to report bugs or suggest any ideas using "Issues" page.

>[!IMPORTANT]
> Please send your pull requests to `dev` repository branch, not `master`.

Thank you for your interest in HyperCPU.

### Authors

HyperCPU is brought to you by:

* [HyperWin](https://github.com/HyperWinX) (2024 - present time) - idea, code, documentation.
* [Ivan Movchan](https://github.com/ivan-movchan) (2025 - present time) - artwork, beta testing, sample programs.

### License

HyperCPU is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
