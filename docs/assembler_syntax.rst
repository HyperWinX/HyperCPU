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
    - [0x0]
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

----------
Directives
----------
| Assembler supports directives for inserting raw data. Syntax:

.. code-block::

  .b<size> <imm>;

| Examples:

.. code-block::

  .b8 0b01010101;
  .b16 0u65535;
  .b32 0xAF5508AC;
  .b64 0xFFAAFFAAFFAAFFAA;

| You also can substitute b64 values with labels! Just like this:

.. code-block::

  .b64 handler;
  handler:
    // Some code
    halt;

| But you can do that only with b64 values, not less.

-------------
Code examples
-------------
| So, let me show you some examples, so you can understand how to actually use assembler.

.. code-block::

  print: // Define label "print"
    write xlll2, 'H'; // Write 'H' to stdout
    write xlll2, '!'; // Write '!' to stdout
    halt; // Shutdown emulator
  _start:
    mov x1, 0xFFF; // Move immediate value 0xFFF into x1 register
    mov x0, [x1]; // Load value from address 0xFFF, stored in register x1, into register x0
    /* These two instructions have no relation to the printing function! I just showed you syntax. */
    jmp print; // Jump to the function "print"


