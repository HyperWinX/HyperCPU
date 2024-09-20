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


========================
ADC - Add With Carry
========================

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


========================
ADD - Add With Carry
========================

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
| Adds the source operand (second operand) and the carry flag to destination operand (first operand).
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| Overflow flag set if result is overflown.


========================
AND - Logical AND
========================

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


========================
ANDN - Logical AND NOT
========================

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
| Performs a bitwise AND operation on the destination and source operands, and stores the result in the destination operand location.
| The source operand can be either register, memory address or immediate value.
| The destination operand is a register.

| **Exceptions**:
| IA - access to invalid memory area.

| **Flags affected**:
| None.


========================
BSWAP - Byte Swap
========================

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
| The destination operand is a register.

| **Exceptions**:
| None.

| **Flags affected**:
| None.

========================
CALL - Call procedure
========================

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

========================
MOV - Move
========================

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


========================
CCRF - Clear Carry Flag
========================

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


========================
COVF - Clear Overflow Flag
========================

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


========================
CUDF - Clear Undeflow Flag
========================

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

========================
HID - HyperCPU ID
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0A000A<imm>
    - hid <imm8>
    - IMM

| **Description**:
| Fetches information about CPU. Acts as **nop** if unsupported value is passed.

.. list-table:: Possible values
  :widths: 4 50
  :header-rows: 1

  * - Hex value
    - Returned value

  * - 00
    - Returns maximum value that **hid** can accept.
  
  * - 01
    - Fetch CPU name and version. Result is stored as string in x0-x3.
  
  * - 02
    - x0 becomes bit mask of supported instruction sets. Right now there is no additional instruction sets - does nothing.


| **Exceptions**:
| None.

| **Flags affected**:
| None


========================
INC - Increment register value.
========================

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


========================
DEC - Decrement register value.
========================

.. list-table:: Possible usage
  :widths: 17 21 15
  :header-rows: 1

  * - Opcode
    - Instruction
    - Operands type
  * - 0B0008<r>
    - dec <r8>
    - R
  * - 0B0048<r>
    - dec <r16>
    - R
  * - 0B0088<r>
    - dec <r32>
    - R
  * - 0B00C8<r>
    - dec <r64>
    - R

| **Description**:
| Increments register value.

| **Exceptions**:
| None.

| **Flags affected**:
| UDF -> set, if value has been underflown.
| UDF -> not set, if value has not been underflown.