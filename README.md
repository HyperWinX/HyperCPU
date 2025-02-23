<div align="center">
     <picture>
          <source media="(prefers-color-scheme: dark)" srcset="images/logo_dark.png">
          <source media="(prefers-color-scheme: light)" srcset="images/logo.png">
          <img alt="HyperCPU" src="images/logo.png">
     </picture>
</div>

<h4 align="center">HyperCPU - the <i>hyper</i> toolkit for custom <i>hyper</i> ISA</h4>

<p align="center">
	<a href="#what-is-it">What is it?</a>
	|
	<a href="#roadmap">Roadmap</a>
	|
	<a href="#installation">Installation</a>
	|
	<a href="#usage">Usage</a>
	|
	<a href="#contributing">Contributing</a>
	|
	<a href="#authors">Authors</a>
	|
	<a href="#license">License</a>
</p>

<p align="center">
     <a href="https://github.com/HyperWinX/HyperCPU/issues">
     <img src="https://img.shields.io/github/issues/HyperWinX/HyperCPU"
          alt="GitHub opened issues"></a>
     <img src="https://img.shields.io/badge/version-0.2.5-red"
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
> HyperCPU is almost ready for use! Wait for 1.0 release to try it out or build the project locally, test and report found issues.

<img alt="HyperCPU screenshot" src="images/screenshot.png">

## What is it?

HyperCPU is a set of programs, created to work with my own simple ISA (instruction set architecture). The project was created for fun, but it took a lot of time (and nerves), and I learned a lot while working on it.

HyperCPU toolkit includes:
* **hCPU emulator**;
* **hASM assembler**;
* **hASM disassembler**.

>[!WARNING]
> HyperCPU supports Linux systems only. Do not even try to build it under Windows.

## Roadmap

You can find the project roadmap [here](ROADMAP.md).

## Installation

At the moment of writing this text, HyperCPU installation is done by building the whole project from source codes. Maybe one day HyperCPU will start distributing release tarballs for much easier installation, but who knows.

### Building from source codes

HyperCPU requires these tools and libraries:

* C++ compiler with C++23 standard support (i. e. `gcc` >= `14`);
* `clang` >= `19`;
* `cmake`, `ninja` - build systems;
* `re2` - regular expressions parser;
* `libfmt` - formatting library;
* `googletest` - required for building tests in Release build profile;
* `python3`, `python3-pip`, `sphinx` and `sphinx-rtd-theme` (should be installed through `pip` or your system package manager) - required for building a documentation.

There are a few options (definitions) that can be used with `cmake`:
* `CMAKE_BUILD_TYPE`:`STRING` - project build profile (`Release` or `Debug`), should be always specified;
* `HCPU_SANITIZERS_ENABLED`:`BOOL` - HyperCPU sanitizers (enabled by default); use `-DHCPU_SANITIZERS_ENABLED:BOOL=OFF` to disable them.

After installing dependencies, open the terminal and run these commands:

```bash
git clone https://github.com/HyperWinX/HyperCPU --recursive
cd HyperCPU
cmake -S. -Bbuild -G "Ninja" -DCMAKE_BUILD_TYPE=Release
ninja -C build default -j$(nproc)
```

That's all. The compiled binaries should be located in `build` directory.

Run `cd docs && make html` to build a documentation. After that go to `docs/_build/html` directory, open `index.html` and start reading.

## Usage

```
Usage: hcasm [--help] [--version] [-o VAR] [-c] [-v VAR] source

Positional arguments:
  source         source file to be assembled [required]

Optional arguments:
  -h, --help     shows help message and exits 
  -v, --version  prints version information and exits 
  -o             name of the binary file 
  -c             compile to object file 
  -v             set verbosity level. possible modes:
                 - debug
                 - info
                 - warning
                 - error [nargs=0..1] [default: "warning"]

Usage: hcemul [--help] [--version] [-v VAR] binary

Positional arguments:
  binary         binary file to execute [required]

Optional arguments:
  -h, --help     shows help message and exits 
  -v, --version  prints version information and exits 
  -v             set verbosity level. possible modes:
                 - debug
                 - info
                 - warning
                 - error [nargs=0..1] [default: "debug"]
```

## Contributing

HyperCPU is in active development, and we will be happy to hear any feedback from you. Do not hesitate to report bugs or suggest any ideas using "Issues" page.

>[!IMPORTANT]
>Please send your pull requests to `dev` repository branch (not `master`).

Thank you for your interest in HyperCPU.

## Authors

* [HyperWin](https://github.com/HyperWinX) (2024 - present time) - idea, code, documentation.
* [Ivan Movchan](https://github.com/ivan-movchan) (2025 - present time) - artwork.

## License

HyperCPU is a free software licensed under [GNU General Public License 3.0](LICENSE).