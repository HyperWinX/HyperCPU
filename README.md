<div align="center">
     <picture>
          <source media="(prefers-color-scheme: dark)" srcset="git/logo_dark.png">
          <source media="(prefers-color-scheme: light)" srcset="git/logo.png">
          <img alt="yes" src="https://user-images.githubusercontent.com/25423296/163456779-a8556205-d0a5-45e2-ac17-42d089e3c3f8.png">
     </picture>
</div>

<h4 align="center">Toolkit for custom ISA</h4>

<p align="center">
     <a href="https://github.com/HyperWinX/HyperCPU/issues">
     <img src="https://img.shields.io/github/issues/HyperWinX/HyperCPU"
          alt="GitHub opened issues">
     <img src="https://img.shields.io/badge/version-0.2.0-red"
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

<table>
<tr>
<td>

HyperCPU is a set of programs, created to work with my own simple ISA.
Project was created for fun, but took a lot of time, and i learned a lot in process. 

</td>
</tr>
</table>

>[!IMPORTANT]
> Project is almost ready to be used. Wait for 1.0 release to try it out, or build it locally, test and report found issues.

Tools include:
- **hCPU emulator**
- **hASM assembler**
- **hASM disassembler**

### Roadmap
You can find roadmap [here](roadmap.md).

## Building guide
>[!WARNING]
> Project requires compiler with C++23 support. CLang 19 and GCC 14 satisfy that requirement.
### Dependencies
HyperCPU project has some external dependencies, like:
- re2
- libfmt
- googletest (optional, required for building tests on Release profile)  
  
To install them, use the following listing:  
  
APT-based distros:
```
sudo apt install libre2-dev libfmt-dev libgtest-dev googletest
```
  
Pacman-based distros:
```
sudo pacman -S re2 fmt gtest
```
  
Portage-based distros:
```
sudo emerge re2 libfmt gtest
```
  
### Building project
```
git clone https://github.com/HyperWinX/HyperCPU --recursive && cd HyperCPU
cmake -S. -Bbuild -G "Ninja" -DCMAKE_BUILD_TYPE=Release
ninja -C build default -j8
```
  
That's all, all tools are built.

### Configuring CMake
Available options:
- CMAKE_BUILD_TYPE:STRING - should be always specified. Release and Debug builds are available.
- HCPU_SANITIZERS_ENABLED:BOOL - sanitizers are always enabled even in Release build. Use -DHCPU_SANITIZERS_ENABLED:BOOL=OFF to disable them.

### Building documentation
Building documentation requires sphinx installed. After you installed sphinx, go to docs directory and do:
```
make html
```
After that, you will get output in docs/_build/html directory. Open index.html to get started.
