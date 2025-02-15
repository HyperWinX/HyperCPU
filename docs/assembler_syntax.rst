Assembler syntax reference
==========================

--------
Operands
--------
| Possible operand types are: R (register), RM (use register as memory address), M (memory address) and IMM (immediate value)
| Following table shows possible syntax for every type:

.. list-table:: Operands syntax
  :widths: 15 15 60
  :header-rows: 1

  * - Operand type
    - Syntax
    - Description
  * - R
    - x0
    - Any register name, except unavailable ones
  * - RM
    - [x0]
    - Any 64bit register, square brackets mean "use value as an address"
  * - M
    - [0h]
    - Any hex(!) value. Only hex values are supported
  * - IMM
    - 0s15 | 0u15 | 0x15 | 0b01001001010
    - One of the following formats are supported. Signed integer, unsigned, hex, and binary

| Operands are separated by comma.

------------
Instructions
------------
| Now, instructions - whole statements. One instruction contains name of the opcode, and from zero to two operands.
| Examples below:

.. list-table:: Example instructions
  :widths: 15 30
  :header-rows: 1

  * - Syntax
    - Description
  * - mov x0, [x1];
    - Move to x0 value from memory address, taken from x1 register.
  * - call x2;
    - Call address, taken from x2 register;
  * - halt;
    - Halt CPU.


------
Labels
------
| Also, you can define labels, and reference them. Assembler is able to resolve references to labels
| you didn't yet defined. Examples:

.. list-table:: Using labels
  :widths: 15 30
  :header-rows: 1

  * - Code
    - Description
  * - _start:
    - Define label called _start
  * - call _start;
    - Call code after label _start;
  * - mov x0, _start;
    - Move address of label (first instruction after it) to the x0 register
