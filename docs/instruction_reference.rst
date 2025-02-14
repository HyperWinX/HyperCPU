Instruction reference
=====================

----------
Main terms
----------

* r8 - 8 bit register
* r16 - 16 bit register
* r32 - 32 bit register
* r64 - 64 bit register
* rm - interpret register value as address
* m - immediate memory address
* m8 - 8 bits from immediate memory address
* m16 - 16 bits from immediate memory address
* m32 - 32 bits from immediate memory address
* m64 - 64 bits from immediate memory address
* imm8 - immediate 8 bit value
* imm16 - immediate 16 bit value
* imm32 - immediate 32 bit value
* imm64 - immediate 64 bit value

----------------------
'Opcode' field meaning
----------------------
* <m> - memory address. Size - 64 bit
* <r> - encoded register. Size - 8 bit
* <imm> - immediate value. Size - (8 - 64) bit


====================
ADC - Add With Carry
====================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 010000<r><r>
    - add <r8>, <r8>
    - R_R
  * - 010040<r><r>
    - add <r16>, <r16>
    - R_R
  * - 010080<r><r>
    - add <r32>, <r32>
    - R_R
  * - 0100C0<r><r>
    - add <r64>, <r64>
    - R_R
  * - 010001<r><r>
    - add <r8>, <rm>
    - R_RM
  * - 010041<r><r>
    - add <r16>, <rm>
    - R_RM
  * - 010081<r><r>
    - add <r32>, <rm>
    - R_RM
  * - 0100C1<r><r>
    - add <r64>, <rm>
    - R_RM
  * - 010002<r><m>
    - add <r8>, <m8>
    - R_M
  * - 010042<r><m>
    - add <r16>, <m16>
    - R_M
  * - 010082<r><m>
    - add <r32>, <m32>
    - R_M
  * - 0100C2<r><m>
    - add <r64>, <m64>
    - R_M
  * - 010003<r><imm>
    - add <r8>, <imm8>
    - R_IMM
  * - 010043<r><imm>
    - add <r16>, <imm16>
    - R_IMM
  * - 010083<r><imm>
    - add <r32>, <imm32>
    - R_IMM
  * - 0100C3<r><imm>
    - add <r64>, <imm64>
    - R_IMM


| **Description**:
| Adds the source operand (second operand) and the carry flag to destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.


=========
ADD - Add
=========

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 020000<r><r>
    - add <r8>, <r8>
    - R_R
  * - 020040<r><r>
    - add <r16>, <r16>
    - R_R
  * - 020080<r><r>
    - add <r32>, <r32>
    - R_R
  * - 0200C0<r><r>
    - add <r64>, <r64>
    - R_R
  * - 020001<r><r>
    - add <r8>, <rm>
    - R_RM
  * - 020041<r><r>
    - add <r16>, <rm>
    - R_RM
  * - 020081<r><r>
    - add <r32>, <rm>
    - R_RM
  * - 0200C1<r><r>
    - add <r64>, <rm>
    - R_RM
  * - 020002<r><m>
    - add <r8>, <m8>
    - R_M
  * - 020042<r><m>
    - add <r16>, <m16>
    - R_M
  * - 020082<r><m>
    - add <r32>, <m32>
    - R_M
  * - 0200C2<r><m>
    - add <r64>, <m64>
    - R_M
  * - 020003<r><imm>
    - add <r8>, <imm8>
    - R_IMM
  * - 020043<r><imm>
    - add <r16>, <imm16>
    - R_IMM
  * - 020083<r><imm>
    - add <r32>, <imm32>
    - R_IMM
  * - 0200C3<r><imm>
    - add <r64>, <imm64>
    - R_IMM

| **Description**:
| Adds the source operand (second operand) to destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.


=================
AND - Logical AND
=================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 030000<r><r>
    - and <r8>, <r8>
    - R_R
  * - 030040<r><r>
    - and <r16>, <r16>
    - R_R
  * - 030080<r><r>
    - and <r32>, <r32>
    - R_R
  * - 0300C0<r><r>
    - and <r64>, <r64>
    - R_R
  * - 030001<r><r>
    - and <r8>, <rm>
    - R_RM
  * - 030041<r><r>
    - and <r16>, <rm>
    - R_RM
  * - 030081<r><r>
    - and <r32>, <rm>
    - R_RM
  * - 0300C1<r><r>
    - and <r64>, <rm>
    - R_RM
  * - 030002<r><m>
    - and <r8>, <m8>
    - R_M
  * - 030042<r><m>
    - and <r16>, <m16>
    - R_M
  * - 030082<r><m>
    - and <r32>, <m32>
    - R_M
  * - 0300C2<r><m>
    - and <r64>, <m64>
    - R_M
  * - 030003<r><imm>
    - and <r8>, <imm8>
    - R_IMM
  * - 030043<r><imm>
    - and <r16>, <imm16>
    - R_IMM
  * - 030083<r><imm>
    - and <r32>, <imm32>
    - R_IMM
  * - 0300C3<r><imm>
    - and <r64>, <imm64>
    - R_IMM

| **Description**:
| Performs a bitwise AND operation on the destination and source operands, and stores the result in the destination operand location.
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.


======================
ANDN - Logical AND NOT
======================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 040000<r><r>
    - andn <r8>, <r8>
    - R_R
  * - 040040<r><r>
    - andn <r16>, <r16>
    - R_R
  * - 040080<r><r>
    - andn <r32>, <r32>
    - R_R
  * - 0400C0<r><r>
    - andn <r64>, <r64>
    - R_R
  * - 040001<r><r>
    - andn <r8>, <rm>
    - R_RM
  * - 040041<r><r>
    - andn <r16>, <rm>
    - R_RM
  * - 040081<r><r>
    - andn <r32>, <rm>
    - R_RM
  * - 0400C1<r><r>
    - andn <r64>, <rm>
    - R_RM
  * - 040002<r><m>
    - andn <r8>, <m8>
    - R_M
  * - 040042<r><m>
    - andn <r16>, <m16>
    - R_M
  * - 040082<r><m>
    - andn <r32>, <m32>
    - R_M
  * - 0400C2<r><m>
    - andn <r64>, <m64>
    - R_M
  * - 040003<r><imm>
    - andn <r8>, <imm8>
    - R_IMM
  * - 040043<r><imm>
    - andn <r16>, <imm16>
    - R_IMM
  * - 040083<r><imm>
    - andn <r32>, <imm32>
    - R_IMM
  * - 0400C3<r><imm>
    - andn <r64>, <imm64>
    - R_IMM

| **Description**:
| Performs a bitwise ANDN operation on the destination and source operands, and stores the result in the destination operand location.
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.


=================
BSWAP - Byte Swap
=================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 050008<r>
    - bswap <r8>
    - R
  * - 050048<r>
    - bswap <r16>
    - R
  * - 050088<r>
    - bswap <r32>
    - R
  * - 0500C8<r>
    - bswap <r64>
    - R

| **Description**:
| Performs a byte swap operation on destination register. If 8 bit register is passed - works as NOP.
| If r8 is passed: does no effect.
| The destination operand is a register.

| **Exceptions**:
| None.

| **Flags affected**:
| None.

=====================
CALL - Call procedure
=====================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0600C8<r>
    - call <r64>
    - R
  * - 0600C9<m>
    - call <m>
    - M

| **Description**:
| Performs a call procedure to address, specified by destination operand
| The destination operand is a register or a memory address.

| **Exceptions**:
| None.

| **Flags affected**:
| None.


=======================
CCRF - Clear Carry Flag
=======================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 070000
    - ccrf
    - NONE

| **Description**:
| Clears carry flag. Accepts no operands

| **Exceptions**:
| None.

| **Flags affected**:
| CRF -> not set.


==========================
COVF - Clear Overflow Flag
==========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 080000
    - covf
    - NONE

| **Description**:
| Clears overflow flag. Accepts no operands

| **Exceptions**:
| None.

| **Flags affected**:
| OVF -> not set.


==========================
CUDF - Clear Undeflow Flag
==========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 090000
    - cudf
    - NONE

| **Description**:
| Clears underflow flag. Accepts no operands

| **Exceptions**:
| None.

| **Flags affected**:
| UDF -> not set.


===============================
DEC - Decrement register value.
===============================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0C0008<r>
    - dec <r8>
    - R
  * - 0C0048<r>
    - dec <r16>
    - R
  * - 0C0088<r>
    - dec <r32>
    - R
  * - 0C00C8<r>
    - dec <r64>
    - R

| **Description**:
| Increments register value.

| **Exceptions**:
| None.

| **Flags affected**:
| UDF -> set, if value has been underflown.
| UDF -> not set, if value has not been underflown.


===========================
DIV - Divide integer value.
===========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0D0008<r>
    - div <r8>
    - R
  * - 0D0048<r>
    - div <r16>
    - R
  * - 0D0088<r>
    - div <r32>
    - R
  * - 0D00C8<r>
    - div <r64>
    - R

| **Description**:
| Divide value, stored in specified register, by divider in x2, and save remainder in x1.

| **Exceptions**:
| ZRDIV -> is raised when division by zero happens.

| **Flags affected**:
| None.


===========
HALT - Halt
===========

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 130000
    - or
    - NONE

| **Description**:
| Halts the CPU.

| **Exceptions**:
| None.

| **Flags affected**:
| None.


=================
HID - HyperCPU ID
=================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0A000A
    - hid
    - IMM

| **Description**:
| Fetches information about CPU. Acts as **nop** if unsupported argument is passed. Argument is passed in **x0** register.

.. list-table:: Possible values
  :widths: 4 50
  :header-rows: 1

  * - Hex value
    - Returned value

  * - 00
    - Stores maximum value that **hid** can accept in register x0.
  
  * - 01
    - Fetch CPU name and version. Result is stored as string in registers x0-x3.
  
  * - 02
    - x0 becomes bit mask of supported instruction sets. Right now there is no additional instruction sets - does nothing.


| **Exceptions**:
| None.

| **Flags affected**:
| None

===============================
INC - Increment register value.
===============================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0B0008<r>
    - inc <r8>
    - R
  * - 0B0048<r>
    - inc <r16>
    - R
  * - 0B0088<r>
    - inc <r32>
    - R
  * - 0B00C8<r>
    - inc <r64>
    - R

| **Description**:
| Increments register value.

| **Exceptions**:
| None.

| **Flags affected**:
| OVF -> set, if value has been overflown.
| OVF -> not set, if value has not been overflown.


==========
MOV - Move
==========

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type

  * - 7F0000<r><r>
    - mov <r8>, <r8>
    - R_R
  * - 7F0040<r><r>
    - mov <r16>, <r16>
    - R_R
  * - 7F0080<r><r>
    - mov <r32>, <r32>
    - R_R
  * - 7F00C0<r><r>
    - mov <r64>, <r64>
    - R_R

  * - 7F0001<r><r>
    - mov <r8>, <rm>
    - R_RM
  * - 7F0041<r><r>
    - mov <r16>, <rm>
    - R_RM
  * - 7F0081<r><r>
    - mov <r32>, <rm>
    - R_RM
  * - 7F00C1<r><r>
    - mov <r64>, <rm>
    - R_RM

  * - 7F0002<r><m>
    - mov <r8>, <m8>
    - R_M
  * - 7F0042<r><m>
    - mov <r16>, <m16>
    - R_M
  * - 7F0082<r><m>
    - mov <r32>, <m32>
    - R_M
  * - 7F00C2<r><m>
    - mov <r64>, <m64>
    - R_M

  * - 7F0003<r><imm>
    - mov <r8>, <imm8>
    - R_IMM
  * - 7F0043<r><imm>
    - mov <r16>, <imm16>
    - R_IMM
  * - 7F0083<r><imm>
    - mov <r32>, <imm32>
    - R_IMM
  * - 7F00C3<r><imm>
    - mov <r64>, <imm64>
    - R_IMM

  * - 7F0004<r><r>
    - mov <rm>, <r8>
    - RM_R
  * - 7F0044<r><r>
    - mov <rm>, <r16>
    - RM_R
  * - 7F0084<r><r>
    - mov <rm>, <r32>
    - RM_R
  * - 7F00C4<r><r>
    - mov <rm>, <r64>
    - RM_R

  * - 7F0005<r><m>
    - mov <rm>, <m8>
    - RM_M
  * - 7F0045<r><m>
    - mov <rm>, <m16>
    - RM_M
  * - 7F0085<r><m>
    - mov <rm>, <m32>
    - RM_M
  * - 7F00C5<r><m>
    - mov <rm>, <m64>
    - RM_M

  * - 7F0006<r><imm>
    - mov <rm>, <imm8>
    - RM_IMM
  * - 7F0046<r><imm>
    - mov <rm>, <imm16>
    - RM_IMM
  * - 7F0086<r><imm>
    - mov <rm>, <imm32>
    - RM_IMM
  * - 7F00C6<r><imm>
    - mov <rm>, <imm64>
    - RM_IMM

  * - 7F0007<m><r>
    - mov <m8>, <r8>
    - M_R
  * - 7F0047<m><r>
    - mov <m16>, <r16>
    - M_R
  * - 7F0087<m><r>
    - mov <m32>, <r32>
    - M_R
  * - 7F00C7<m><r>
    - mov <m64>, <r64>
    - M_R

| **Description**:
| Copies the value of the second operand to the first operand.
| The source can be either a register, a memory location, or an immediate value.
| The destination can be either a register or a memory location.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.


=============================
MUL - Multiply integer value.
=============================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0E0000<r><r>
    - mul <r8> <r8>
    - R_R
  * - 0E0040<r><r>
    - mul <r16> <r16>
    - R_R
  * - 0E0080<r><r>
    - mul <r32> <r32>
    - R_R
  * - 0E00C0<r><r>
    - mul <r64> <r64>
    - R_R
  * - 0E0001<r><r>
    - mul <r8> <r64>
    - R_RM
  * - 0E0041<r><r>
    - mul <r16> <r64>
    - R_RM
  * - 0E0081<r><r>
    - mul <r32> <r64>
    - R_RM
  * - 0E00C1<r><r>
    - mul <r64> <r64>
    - R_RM
  * - 0E0002<r><m>
    - mul <r8> <m>
    - R_M
  * - 0E0042<r><m>
    - mul <r16> <m>
    - R_M
  * - 0E0082<r><m>
    - mul <r32> <m>
    - R_M
  * - 0E00C2<r><m>
    - mul <r64> <m>
    - R_M
  * - 0E0003<r><imm>
    - mul <r8> <imm8>
    - R_IMM
  * - 0E0043<r><m>
    - mul <r16> <imm16>
    - R_IMM
  * - 0E0083<r><m>
    - mul <r32> <imm32>
    - R_IMM
  * - 0E00C3<r><m>
    - mul <r64> <imm64>
    - R_IMM

| **Description**:
| Multiply value, specified by operand 1, by value, specified by operand 2.

| **Exceptions**:
| 

| **Flags affected**:
| None.


===============
OR - Logical OR
===============

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 120000<r><r>
    - or <r8>, <r8>
    - R_R
  * - 120040<r><r>
    - or <r16>, <r16>
    - R_R
  * - 120080<r><r>
    - or <r32>, <r32>
    - R_R
  * - 1200C0<r><r>
    - or <r64>, <r64>
    - R_R
  * - 120001<r><r>
    - or <r8>, <rm>
    - R_RM
  * - 120041<r><r>
    - or <r16>, <rm>
    - R_RM
  * - 120081<r><r>
    - or <r32>, <rm>
    - R_RM
  * - 1200C1<r><r>
    - or <r64>, <rm>
    - R_RM
  * - 120002<r><m>
    - or <r8>, <m8>
    - R_M
  * - 120042<r><m>
    - or <r16>, <m16>
    - R_M
  * - 120082<r><m>
    - or <r32>, <m32>
    - R_M
  * - 1200C2<r><m>
    - or <r64>, <m64>
    - R_M
  * - 120003<r><imm>
    - or <r8>, <imm8>
    - R_IMM
  * - 120043<r><imm>
    - or <r16>, <imm16>
    - R_IMM
  * - 120083<r><imm>
    - or <r32>, <imm32>
    - R_IMM
  * - 1200C3<r><imm>
    - or <r64>, <imm64>
    - R_IMM

| **Description**:
| Performs a bitwise OR operation on the destination and source operands, and stores the result in the destination operand location.
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.


=====================
READ - Read From Port
=====================

.. list-table:: Possible usage
   :widths: 17 21 1
   :header-rows: 1

   * - Opcode
     - Instruction
     - Operands type
   * - 180008<r>
     - read <r8>
     - R
   * - 18000F<imm>
     - read <imm8>
     - IMM

| **Description**:
| Read from port, specified by operand, and save value in xlll0 register;

| **Exceptions**:
| None.

| **Flags affected**:
| None.


========================
SHFL - Binary Shift Left
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 110008<r><r>
    - shfl <r8> <r8>
    - R_R
  * - 110048<r><r>
    - shfl <r16> <r16>
    - R_R
  * - 110088<r><r>
    - shfl <r32> <r32>
    - R_R
  * - 1100C8<r><r>
    - shfl <r64> <r64>
    - R_R
  * - 110008<r><imm>
    - shfl <r8> <imm8>
    - R_IMM
  * - 110048<r><imm>
    - shfl <r16> <imm16>
    - R_IMM
  * - 110088<r><imm>
    - shfl <r32> <imm32>
    - R_IMM
  * - 1100C8<r><imm>
    - shfl <r64> <imm64>
    - R_IMM

| **Description**:
| Performs a binary shift left operation on specified register.

| **Exceptions**:
| None.

| **Flags affected**:
| None.

=========================
SHFR - Binary Shift Right
=========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 100008<r><r>
    - shfr <r8> <r8>
    - R_R
  * - 100048<r><r>
    - shfr <r16> <r16>
    - R_R
  * - 100088<r><r>
    - shfr <r32> <r32>
    - R_R
  * - 1000C8<r><r>
    - shfr <r64> <r64>
    - R_R
  * - 100008<r><imm>
    - shfr <r8> <imm8>
    - R_IMM
  * - 100048<r><imm>
    - shfr <r16> <imm16>
    - R_IMM
  * - 100088<r><imm>
    - shfr <r32> <imm32>
    - R_IMM
  * - 1000C8<r><imm>
    - shfr <r64> <imm64>
    - R_IMM

| **Description**:
| Performs a binary shift right operation on specified register.

| **Exceptions**:
| None.

| **Flags affected**:
| None.


=====================
SUB - Subtract values
=====================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0F0000<r><r>
    - sub <r8>, <r8>
    - R_R
  * - 0F0040<r><r>
    - sub <r16>, <r16>
    - R_R
  * - 0F0080<r><r>
    - sub <r32>, <r32>
    - R_R
  * - 0F00C0<r><r>
    - sub <r64>, <r64>
    - R_R
  * - 0F0001<r><r>
    - sub <r8>, <rm>
    - R_RM
  * - 0F0041<r><r>
    - sub <r16>, <rm>
    - R_RM
  * - 0F0081<r><r>
    - sub <r32>, <rm>
    - R_RM
  * - 0F00C1<r><r>
    - sub <r64>, <rm>
    - R_RM
  * - 0F0002<r><m>
    - sub <r8>, <m8>
    - R_M
  * - 0F0042<r><m>
    - sub <r16>, <m16>
    - R_M
  * - 0F0082<r><m>
    - sub <r32>, <m32>
    - R_M
  * - 0F00C2<r><m>
    - sub <r64>, <m64>
    - R_M
  * - 0F0003<r><imm>
    - sub <r8>, <imm8>
    - R_IMM
  * - 0F0043<r><imm>
    - sub <r16>, <imm16>
    - R_IMM
  * - 0F0083<r><imm>
    - sub <r32>, <imm32>
    - R_IMM
  * - 0F00C3<r><imm>
    - sub <r64>, <imm64>
    - R_IMM

| **Description**:
| Subtracts the source operand (second operand) from the destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.

=======================
WRITE - Write From Port
=======================
.. list-table:: Possible usage
   :widths: 17 21 1
   :header-rows: 1                                         
   * - Opcode
     - Instruction
     - Operands type
   * - 190000<r><r>
     - write <r8>, <r8>
     - R_R
   * - 190003<r><imm>
     - write <r8>, <imm8>
     - R_IMM

| **Description**:
| Write data, specified by second operand, to port, specified by first operand.

| **Exceptions**:
| None.

| **Flags affected**:
| None.
