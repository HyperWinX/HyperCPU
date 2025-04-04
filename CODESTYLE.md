## Identifiers
Identifiers, written in PascalCase:
- Namespaces (`namespace HyperCPU {}`)
- Class names (`class CPU;`)
- Functions (`void HyperCPU::CPU::CPU() {}`)
- Folder names
- File names

Identifiers, written in snake_case:
- Local variables
- Class fields

## Whitespaces
- Tabs are two spaces long
- No spaces between parenthesis and arguments. Example:
  - `foo( a );` - bad
  - `foo(a);` - good
- Single space between operators. Example: (example: `int b=5; foo(a+b);` - bad, `int b = 5; foo(a + b);` - good)
  - `int b=5; foo(a+b);` - bad
  - `int b = 5; foo(a + b);` - good

## Header guards
For header guards use `#pragma once`. We support GCC and Clang, and it works perfectly fine even on Debian Stable.

## Forward declarations
Do NOT use forward declarations. Include header files instead.

## Order of includes
1. std* headers
2. cstd* headers
3. c* headers
4. Headers from submodules
5. Headers that belong to project

Every block is separated by empty line. Headers in every block should be sorted from longest to shortest names. Never include headers in double quotes, only in angle brackets.

## Inlining
Functions, that should be marked as `constexpr` and `[[gnu::always_inline]]`:
- Microoperations in ALU implementation
- Getters and setters

## Implicit conversions
Do NOT use or allow implicit conversions. Use static_cast for changing the size of integer, HyperCPU::bit_cast for casting container type to the desired type, and HyperCPU::bit_cast_from to fetch desired type from pointer.
